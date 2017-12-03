//
//  LedMatrix
//  part of Let's make series
//
//  The Cave, 2017
//  https://thecave.cz
//
//  Licensed under MIT License (see LICENSE file for details)
//

$innerX = 43.4;
$innerY = 18.9;
$outerZ = 9.2;
$wall = 1.6;
$outerDia = 5;
$dentZ = 3;

$buttonX = 17.4;
$buttonDia = 6.5;

$usbWidth = 8;
$usbHeight = 2.4;
$usbY = $outerZ-$wall-$usbHeight;
$usbX = ($innerY-$usbWidth)/2;

$cableWidth = 6;
$cableHeight = 2.4;
$cableY = $outerZ-$wall-$cableHeight;
$cableX = ($innerY-$cableWidth)/2;

difference() {
    translate([$outerDia/2,$outerDia/2,$outerDia/2]) minkowski() {
        sphere(d=$outerDia,$fn=50);
        cube([$innerX+$wall*2-$outerDia,$innerY+$wall*2-$outerDia,$outerZ+$outerDia*2]);
    }
    translate([$wall,$wall,$wall]) cube([$innerX,$innerY,$outerZ*4]);
    translate([-1,-1,$outerZ]) cube([$innerX*2,$innerY*2,$outerZ*4]);
    translate([$wall/2+($outerDia-$wall)/2,$wall/2+($outerDia-$wall)/2,$outerZ-$dentZ]) minkowski() {
        cube([$innerX+$wall-($outerDia-$wall),$innerY+$wall-($outerDia-$wall),$outerZ]);
        cylinder(d=$outerDia-$wall,h=$outerZ,$fn=50);
    }
    translate([$wall+$buttonX,$wall+$innerY/2,-1]) cylinder(d=$buttonDia,h=$wall*2,$fn=100);
    
    translate([-1,$wall+$usbX,$wall+$usbY]) cube([$wall+2,$usbWidth, $usbHeight]);
    translate([$innerX+$wall-1,$wall+$cableX,$wall+$cableY]) cube([$wall+2,$cableWidth, $cableHeight]);
}

