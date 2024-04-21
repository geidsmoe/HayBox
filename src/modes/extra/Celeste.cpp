#include "modes/extra/Celeste.hpp"

#define ANALOG_STICK_MIN 1
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 255

Celeste::Celeste(socd::SocdType socd_type) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{&InputState::left,    &InputState::right,   socd_type},
        socd::SocdPair{ &InputState::down,   &InputState::mod_x,   socd_type},
        socd::SocdPair{ &InputState::c_left, &InputState::c_right, socd_type},
        socd::SocdPair{ &InputState::c_down, &InputState::c_up,    socd_type},
    };
}

void Celeste::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    // inverted vertical because using middle finger for up is strongly ingrained in my brain
    outputs.dpadLeft = inputs.left;
    outputs.dpadRight = inputs.right;
    outputs.dpadUp = inputs.down;
    outputs.dpadDown = inputs.mod_x;
    
    outputs.a = inputs.a; // Jump
    outputs.b = inputs.b; // Grab
    outputs.x = inputs.x; // Dash
    outputs.y = inputs.mod_y;
    outputs.triggerLDigital = inputs.r; 
    outputs.triggerRDigital = inputs.z; 
    outputs.buttonR = inputs.up; 

    outputs.buttonL = inputs.lightshield; 
    outputs.select = inputs.midshield; 
    outputs.start = inputs.start;
}

void Celeste::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    UpdateDirections(
        inputs.left,
        inputs.right,
        inputs.down,
        inputs.mod_x,
        inputs.c_left,
        inputs.c_right,
        inputs.c_down,
        inputs.c_up,
        ANALOG_STICK_MIN,
        ANALOG_STICK_NEUTRAL,
        ANALOG_STICK_MAX,
        outputs
    );
}
