#include <iostream>
#include <cstdlib>
#include <rtmidi/RtMidi.h>

int main(int argc, char *argv[]) {

    RtMidiIn *midiIn;

    try {
        midiIn = new RtMidiIn();

    } catch (RtMidiError &error) {
        error.printMessage();
        exit( EXIT_FAILURE );
    }

    unsigned int nPorts = midiIn->getPortCount();
    std::cout << std::endl << "There are " << nPorts << " MIDI input sources available." << std::endl;
    std::string portName;

    // iterate through ports 
    for (int i = 0; i < nPorts; i++) {
        try {
            portName = midiIn->getPortName(i);
        } catch (RtMidiError &error) {
            error.printMessage();
            goto cleanup;
        }

        std::cout << "input " << i+1 << ": " << portName << std::endl;
    }

      // Clean up
    cleanup:
    delete midiIn;
    
    return 0;
}