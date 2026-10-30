# Arc-Reactor-Multi-Ring-Controller

An advanced, highly responsive, and cinematic control system for a multi-ring concentric LED array (93 LEDs total), optimized specifically for 3D-printed Tony Stark Arc Reactor props or cosplay builds.
This software leverages the FastLED library to implement 15 complex geometric animations. The project is split down the middle between high-performance mathematical layouts and movie-accurate, organic plasma/energy simulations.

⚡ Key Features

• Instant Interrupt-Driven Switchboard Engine: Uses a dedicated hardware interrupt loop (attachInterrupt) to process mode switches instantaneously, bypassing the execution queue.
• 100% Non-Blocking Micro-Timing: Completely avoids the blocking delay() function inside animation states. Every pattern runs on localized, deterministic millis() clock differentials for jitter-free runtime.
• Concentric Structural Mapping: Implements discrete ring lookup tables (ringSizes and ringStarts) to dynamically treat nested circular channels as isolated geometrical segments.
• Diffuser-Optimized Luminance Layers: The cinematic modes feature a constant "ambient light floor." They are mathematically engineered to eliminate jarring flashes or dark gaps, allowing colors to blend fluidly beneath 3D-printed diffusion plastics or glass lenses.

🛠️ Hardware Specification

• Microcontroller: Arduino Uno, Nano, Pro Mini, or any ATMega328P variant (supports native pin interrupts).
• LED Framework: WS2812B Concentric Ring Array (93 Pixels total distributed across 6 rings).
• Control Input: Momentary tactile push button wired directly to digital input.

Pinout Mapping

• Data Output Pin: D6 (Drives the WS2812B data path).
• Hardware Interrupt Pin: D2 (Configured with internal pull-up resistors for the tactile button loop).
• System Diagnostics LED: D13 (Onboard LED updates dynamically alongside hardware state transitions).

🧬 Ring Mapping Matrix

The architecture targets an explicit 6-ring hardware setup containing 93 addressable pixels arranged from the outside border inward:

Ring Index	Pixel Capacity	Global Start Index	Description
Ring 0	32 Pixels	0	Outermost Perimeter Accelerator
Ring 1	24 Pixels	32	Secondary Outer Shield Matrix
Ring 2	16 Pixels	56	Mid-Field Magnetic Flux Grid
Ring 3	12 Pixels	72	Mid-Field Secondary Channel
Ring 4	8 Pixels	84	Inner Core Isolation Frame
Ring 5	1 Pixel	92	Central Core Element Anchor


🎬 Animation Modules Index


Geometric & Wave-Front Frameworks (0 - 9)

• 0: Concentric Sync Pulse: Synchronous multi-ring monochromatic breathing with deep breathing offsets.
• 1: Radial Rainbow Wheel: Locked angular velocity calculations forcing all 6 rings to spin synchronized rainbow spokes.
• 2: Tunnel Ripple: High-impact inward-bound sonic steps shooting from Ring 0 directly to the core anchor.
• 3: Concentric Chaser: Independent racing chasers orbiting every single nested ring layer at identical velocities.
• 4: Matrix Sparkle: Localized high-frequency star shimmering isolated within random geometric ring boundaries.
• 5: Vortex Spiral: Step index translation offsets per ring, twisting radial lines into mechanical spiral armatures.
• 6: Ping Pong Bounce: Fluid bidirectional wave tracking that bounces smoothly back and forth from the skin to the core.
• 7: Kaleido Spoke: Quadrant-mirrored cross-sections generating clean geometric bars radiating outwards.
• 8: Heat Wave: Localized one-dimensional Perlin noise interpolation generating a realistic fire grid simulation.
• 9: Orbit Split: Counter-rotational mechanics where even rings orbit clockwise and odd rings spin counter-clockwise.

Cinematic Arc Reactor Simulations (10 - 14)

• 10: Stark Core Steady: High-velocity micro-plasma mapping compounded over a low-frequency respiratory breathing cycle. Blends between an icy sky-blue and a stark cyan.
• 11: I-Beam Charge: Continuous ambient blue baseline overlayed by high-intensity inward-collapsing white wavefronts mimicking charging weapon systems.
• 12: Palladium Decay: Simulates thermal core decay. The array runs a boiling blue baseline layout that organic liquid streams of emerald green and amber warning voltages tear through.
• 13: Vibranium Overload: Spawns a high density of counter-rotating white and cyan energy tracers racing across every ring layer while passing through one another.
• 14: Stark Segment Test: A sweeping 90-degree rotational radar arm scanning across the system, leaving behind a smooth, highly diffused gradient fade trail.

📦 Installation & Deployment

1. Library Requirement: Ensure you have the latest version of the FastLED library installed via the Arduino IDE Library Manager.
2. Circuit Wiring:
	• Connect your WS2812B data line to digital pin 6 via a 330Ω resistor.
	• Connect a momentary button between digital pin 2 and GND. No external pull-up resistor is required.
3. Power Management: The code enforces a maximum power draw boundary of 5V, 5000mA via software constraints. Ensure your battery assembly (e.g., LiPo cell with a 5V step-up or USB power bank) can comfortably manage your deployment requirements.
4. Compile: Flash the sketch directly to your microcontroller via the Arduino IDE.
