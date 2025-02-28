long now, lastMsg = 0;
long sensorsUpdateInterval = 5000;  // tiempo de actualización de los sensores

void on_loop() {

  now = millis();
  if (now - lastMsg > sensorsUpdateInterval) {
    lastMsg = now;
  }
}
