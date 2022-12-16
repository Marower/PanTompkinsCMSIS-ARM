import os
import threading
import glob
import wfdb
import serial
from time import sleep

# Adjust these two variables to your setting
# path to dataset - script works with physionet data format, was tested on  MIT-BIH Arrhythmia Database v1.0.0
folder = 'mit-bih/'
# serial port name
port = 'COM19'


# main loop of the script send sample from database recording and stores response in file
def no_interrupt():
    # This is very slow implementation data are proceeding sample-by-sample
    # It should use buffers from microcontroller (2048 bytes)
    # There is a problem with synchronization writing and reading
    for i in range(len(record.p_signal)):
        int_value = record.p_signal[i][n] * record.adc_gain[n] + record.adc_zero[n]
        send_str = str(int(int_value)) + '\r\n'
        ser.write(send_str.encode())
        ser.flush()
        line = ser.readline()
        while len(line) < 1:
            line = ser.readline()
        f.write(str(int(int_value))+',' + line[0:len(line)-1].decode())


ser = serial.Serial(port, baudrate=20000000, bytesize=8, parity='N', stopbits=1, timeout=0)
ser.set_buffer_size(rx_size=32768, tx_size=32768)
ser.reset_input_buffer()

# initialise device
# data will be sent as human readable strings
ser.write("+++A1\r\n".encode())
sleep(0.1)
received_line = ser.readline()
if received_line != b'OK, done.   \r\n':
    quit()
# select  implementation of Pan - Tompkins based on CMSIS-DSP library
analysisType = 'B3'    # CMSIS-DSP implementation
ser.write(('+++' + analysisType + '\r\n').encode())
sleep(0.1)
ser.readline()

# get list of recording in folder
dataFiles = []
for file in glob.glob(folder + '*.dat'):
    file = file[0:file.find('.')]
    dataFiles.append(file)


filecount = 1
for file in dataFiles:
    print(str(filecount) + '/' + str(len(dataFiles)))
    filecount += 1
    record = wfdb.rdrecord(file)
    for n in range(2):
        # in mit-bih there are two separate ECG channels
        f = open(file + analysisType + str(n) + '.csv', 'w')
        a = threading.Thread(target=no_interrupt)
        a.start()
        a.join()
        f.close()
ser.close()



