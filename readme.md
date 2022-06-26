# Internal Property Viewer
This program is made for tracking any internal property in FlightGear.
## How to use
Copy protocol in `flightgear` folder into `$FG_ROOT/Protocol/`.  
Add `fgfs --generic=socket,out,60,127.0.0.1,2323,udp,altitude-protocol` to flightgear settings.  
Open the pro file in Qt. Then build and run.  
First select the port number from settings, then click start.  
You can save image with `Ctrl+S`  
## Example
![Image](/images/proof.jpg)