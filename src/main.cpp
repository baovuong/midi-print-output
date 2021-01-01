#include <iostream>
#include <rtmidi/RtMidi.h>

using namespace std;

int main(int argc, char *argv[]) {

    try {
        RtMidiIn midin;
        cout << "Hello!" << endl;

    } catch (RtMidiError &error) {
        error.printMessage();
    }
    
    return 0;
}