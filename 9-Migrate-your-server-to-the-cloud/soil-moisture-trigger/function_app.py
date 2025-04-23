import azure.functions as func
import datetime
import json
import logging

app = func.FunctionApp()


@app.event_hub_message_trigger(arg_name="azeventhub", event_hub_name="eventhubname",
                               connection="EventHubConnectionString") 
def eventhub_trigger(azeventhub: func.EventHubEvent):
    logging.info('Python EventHub trigger processed an event: %s',
                azeventhub.get_body().decode('utf-8'))



@app.event_hub_message_trigger(arg_name="azeventhub", event_hub_name="eventhubname",
                               connection="EventHubConnectionString") 
def eventhub_trigger(azeventhub: func.EventHubEvent):
    logging.info('Python EventHub trigger processed an event: %s',
                azeventhub.get_body().decode('utf-8'))



@app.event_hub_message_trigger(arg_name="azeventhub", event_hub_name="eventhubname",
                               connection="EventHubConnectionString") 
def iotHubTrigger(azeventhub: func.EventHubEvent):
    logging.info('Python EventHub trigger processed an event: %s',
                azeventhub.get_body().decode('utf-8'))
