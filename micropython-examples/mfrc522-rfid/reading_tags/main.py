from mfrc522 import MFRC522
from time import sleep_ms

# Creo instancia de lector RFID
reader = MFRC522(spi_id=0, sck=18, miso=16, mosi=19, cs=17, rst=20)

print("Bring TAG closer...")
print("")

# Inicializo lector
reader.init()

while True:
    # No estoy seguro que comando manda
    (stat, tag_type) = reader.request(reader.REQIDL)
    # Chequeo que haya salido bien la transferencia
    if stat == reader.OK:
        # Leo tarjeta
        (stat, uid) = reader.SelectTagSN()
        # Chequeo el resultado de la transferencia
        if stat == reader.OK:
            # Devuelvo el id de la tarjeta como string
            card = " ".join(uid)
            # Imprimo ID de tarjeta
            print("CARD ID: " + card)
    # Espero para no saturar la consola
    sleep_ms(500) 