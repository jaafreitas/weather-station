import paho.mqtt.client as mqtt

mqtt_server = "mqtt_server"

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, rc):
    print("Connected with result code "+str(rc))
    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("station/+/status")
    client.subscribe("station/+/sensor/+")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
	print("<- " + msg.topic + ": " + str(msg.payload.decode("utf-8")))

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(mqtt_server, 1883, 60)

# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.
client.loop_forever()
