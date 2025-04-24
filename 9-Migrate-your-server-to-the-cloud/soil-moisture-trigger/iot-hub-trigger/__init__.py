import logging
import azure.functions as func
import json
import os
from datetime import datetime, timezone
from azure.iot.hub import IoTHubRegistryManager

# How old a message can be before being ignored (in seconds)
CUTOFF_SECONDS = 5

def main(event: func.EventHubEvent):
    try:
        enqueued_time = event.enqueued_time.replace(tzinfo=timezone.utc)
        now = datetime.utcnow().replace(tzinfo=timezone.utc)

        if (now - enqueued_time).total_seconds() > CUTOFF_SECONDS:
            logging.warning(f"⏭️ Skipping old event from {enqueued_time.isoformat()}")
            return

        # Extract the body of the event which contains the JSON message sent by the IoT device
        body = json.loads(event.get_body().decode('utf-8'))
        device_id = event.iothub_metadata['connection-device-id']
        logging.info(f'✅ Received message: {body} from {device_id}')

        # Check soil moisture, turn relay on if less than 15%
        soil_moisture = body['soil-moisture']
        method_payload = {"relay": soil_moisture < 15}

        # Convert payload into a JSON format string
        c2d_message = json.dumps(method_payload)

        # Load the REGISTRY_MANAGER_CONNECTION_STRING from the local.settings.json file
        registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
        registry_manager = IoTHubRegistryManager(registry_manager_connection_string)

        # Send the C2D message
        logging.info(f'📡 Sending direct method request {c2d_message} for device {device_id}')
        registry_manager.send_c2d_message(device_id, c2d_message, properties={"method": "relay"})
        logging.info('✅ Direct method request sent!')

    except Exception as e:
        logging.error(f'❌ Error in processing: {e}')
