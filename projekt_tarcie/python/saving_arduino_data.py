import serial
import csv
import time

ser = serial.Serial('COM8', 9600, timeout=2)
time.sleep(2)

with open("C:/Users/micha/Desktop/projekty/arduino/projekt_tarcie/python/data/data2.csv", "w", newline="") as f:
    writer = csv.writer(f)
    writer.writerow(["czas_ms", "hallValue", "rpm"])
    
    while True:
        line = ser.readline().decode("utf-8").strip()
        if line:    
            print("ZAPIS:", line)
            parts = line.split(",")
            if len(parts) == 3:
                writer.writerow(parts)
                f.flush()