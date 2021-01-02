#include <iostream>
#include <cstdlib>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

#include <rtmidi/RtMidi.h>
#include <signal.h>

bool done;
static void finish(int ignore){ done = true; }


int main(int argc, char *argv[]) {

    RtMidiIn *midiIn;
    std::string portName;
    int chosenPort, i, nBytes;
    double stamp;
    std::vector<unsigned char> message;

    try {
        midiIn = new RtMidiIn();

    } catch (RtMidiError &error) {
        error.printMessage();
        exit( EXIT_FAILURE );
    }

    unsigned int nPorts = midiIn->getPortCount();
    std::cout << std::endl << "There are " << nPorts << " MIDI input sources available." << std::endl;


    // iterate through ports 
    for (i = 0; i < nPorts; i++) {
        try {
            portName = midiIn->getPortName(i);
        } catch (RtMidiError &error) {
            error.printMessage();
            break;
        }

        std::cout << "input " << i+1 << ": " << portName << std::endl;
    }

    // choose midi device to read
    std::cout << "Choose a device[1-" << nPorts << "]: ";
    std::cin >> chosenPort;

    try {
        std::cout << "chosen device: " << midiIn->getPortName(chosenPort-1) << std::endl;
    } catch (RtMidiError &error) {
        error.printMessage();
    }

    midiIn->openPort(chosenPort);

    // Don't ignore sysex, timing, or active sensing messages.
    midiIn->ignoreTypes( false, false, false );
    done = false;
    (void) signal(SIGINT, finish);

    while (!done) {
        stamp = midiIn->getMessage( &message );
        nBytes = message.size();
        for ( i=0; i<nBytes; i++ )
            std::cout << "Byte " << i << " = " << (int)message[i] << ", ";
        if ( nBytes > 0 )
            std::cout << "stamp = " << stamp << std::endl;
        
        // Sleep for 10 milliseconds ... platform-dependent.
        std::this_thread::sleep_for (std::chrono::milliseconds(10));

    }

    delete midiIn;
    
    return 0;
}