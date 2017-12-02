//
//  LedMatrix
//  part of Let's make series
//
//  The Cave, 2017
//  https://thecave.cz
//
//  Licensed under MIT License (see LICENSE file for details)
//

$innerX = 43.5;
$innerY = 19;
$outerZ = 9.3;
$wall = 1.6;
$outerDia = 5;
$dentZ = 2.5;

$usbWidth = 8;
$usbHeight = 4;
$usbY = $outerZ-$wall-$usbHeight;
$usbX = ($innerY-$usbWidth)/2;

$cableWidth = 6;
$cableHeight = 2;
$cableY = $outerZ-$wall-$cableHeight;
$cableX = ($innerY-$cableWidth)/2;

$spacerSize = 2;
$spacerHeight = 2;


module base() {
    difference() {
        translate([$outerDia/2,$outerDia/2,$outerDia/2]) minkowski() {
            sphere(d=$outerDia,$fn=50);
            cube([$innerX+$wall*2-$outerDia,$innerY+$wall*2-$outerDia,$outerZ+$outerDia*2]);
        }
        translate([$wall,$wall,$wall]) cube([$innerX,$innerY,$outerZ*2]);
        translate([-1,-1,$outerZ-$dentZ]) cube([$innerX*2,$innerY*2,$outerZ*2]);
    }
}

module dent() {
    translate([$outerDia/2,$outerDia/2,$outerZ-$dentZ]) difference() {
        minkowski() {
            cube([$innerX+$wall-($outerDia-$wall),$innerY+$wall-($outerDia-$wall),$dentZ/2]);
            cylinder(d=$outerDia-$wall-0.3,h=$dentZ/2,$fn=50);
        }
        translate([-$outerDia/2+$wall,-$outerDia/2+$wall,-1]) cube([$innerX,$innerY,$dentZ+2]);
    }
}


difference() {
    union() {
        base();
        dent();
    }
    translate([$innerX+$wall-1,$wall+$usbX,$wall+$usbY]) cube([$wall+2,$usbWidth, $usbHeight]);
    translate([-1,$wall+$cableX,$wall+$cableY]) cube([$wall+2,$cableWidth, $cableHeight]);
}

translate([$wall,$wall+$innerY-$spacerSize,$wall]) cube([$spacerSize, $spacerSize, $spacerHeight]);
translate([$wall,$wall,$wall]) cube([$spacerSize, $spacerSize, $spacerHeight]);



