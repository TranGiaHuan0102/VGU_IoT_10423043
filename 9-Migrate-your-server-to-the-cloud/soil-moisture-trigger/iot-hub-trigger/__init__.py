import logging
import azure.functions as func
import json
import os
from azure.iot.hub import IoTHubRegistryManager


def main(event: func.EventHubEvent):
    # Extract the body of the event which contains the JSON message sent by the IoT device
    # Get the device ID from the annotations passed with the message
    # Log this information
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']
    logging.info(f'Received message: {body} from {device_id}')


    # Check soil moisture, turn relay on if less than 15%
    soil_moisture = body['soil-moisture']
    if soil_moisture < 15:
        method_payload = {"relay": True}
    else:
        method_payload = {"relay": False}

    # Convert payload into a JSON Format dict    
    c2d_message = (json.dumps(method_payload))

    # Load the REGISTRY_MANAGER_CONNECTION_STRING from the local.settings.json file
    # Create an instance of the Registry Manager helper class using the connection string
    logging.info(f'Sending direct method request for {c2d_message} for device {device_id}')
    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)

    # Tell the registry manager to send via C2D
    registry_manager.send_c2d_message(device_id, c2d_message, properties={"method": "relay"})
    logging.info('Direct method request sent!')