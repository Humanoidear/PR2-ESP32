void suscribirseATopics() {

  // TODO: añadir suscripciones a los topics MQTT ...
  mqtt_subscribe(TOPIC);
  mqtt_subscribe(TOPIC2);
  mqtt_subscribe(TOPIC3);
}

void alRecibirMensajePorTopic(char* topic, String incomingMessage) {

  // TODO: Controlador que gestiona la recepción de datos

  // A partir de aquí debemos gestionar los mensajes
  //  recibidos por los diferentes topics (canales)
  //

  // If a message is received on the topic ...
  if (strcmp(topic, TOPIC2) == 0) {
    if (incomingMessage == "ON") {
      mqtt_publish(TOPIC3, "TODO: Encender el led interno");
      digitalWrite(9, HIGH);
    } else if (incomingMessage == "OFF") {
      mqtt_publish(TOPIC3, "TODO: Apagar el led interno");
      digitalWrite(9, LOW);
    } else warnln("**>> Solicitud no reconocida!");
  }
}

void enviarMensajePorTopic(const char* topic, String outgoingMessage) {

  mqtt_publish(topic, outgoingMessage.c_str());
}
