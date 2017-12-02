//  The Cave, 2017
//  https://thecave.cz
//
//  Licensed under MIT License (see LICENSE file for details)
//

$buttonDia = 6;
$buttonRimDia = 7.5;
$buttonRimHeight = 0.4;
$buttonHeight = 3;

cylinder(d=$buttonDia,h=$buttonHeight,$fn=100);
cylinder(d=$buttonRimDia,h=$buttonRimHeight,$fn=100);