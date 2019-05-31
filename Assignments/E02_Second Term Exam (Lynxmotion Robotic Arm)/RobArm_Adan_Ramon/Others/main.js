function degreeToRadian( angle){
    return angle * (Math.PI / 180);
}



const distacciaPlaca=17
const gradosDistacciaPlaca=55
const radDistacciaPlaca=degreeToRadian(gradosDistacciaPlaca)
const ladoBase=9
var baseCentro=Math.sqrt(Math.pow(ladoBase, 2)+Math.pow(ladoBase, 2))/2
var hypTocenter=Math.sqrt(Math.pow(baseCentro,2)+Math.pow(distacciaPlaca,2))
var radCenter=Math.asin(baseCentro/hypTocenter)


var radmiss=(Math.PI/2)-(radCenter+radDistacciaPlaca)

var thrx=Math.sin(radmiss)*hypTocenter
var thry=Math.cos(radmiss)*hypTocenter






// Arm Specification
const xbase=0.0
const ybase=0.0


const baseHeight=5.0
const longShoulderElbow=15
const longElbowHand=15

//Piece
const topPiece = 2


// location SHERLOCK
var toPlace = [10.0, 20.0]
var toPick = [10.0, 20.0]


// To single vars
var xPick=toPick[0]+thrx
var yPick=toPick[1]+thry

var xPlace=toPlace[0]+thrx
var yPlace=toPlace[1]+thry

// Set camera

/////////////////////////// Picking ////////////////////////////
var plainDistance = Math.sqrt(Math.pow((y-ybase), 2)+Math.pow((x-xbase), 2))
var baseAngle = Math.asin((y-ybase)/plainDistance)
// move shoulder to angle in base reference
var rectSide=baseHeight - topPiece
var hiposide = Math.sqrt(Math.pow(rectSide,2)+Math.pow(plainDistance, 2))
var cosA=(Math.pow(longShoulderElbow,2)+ Math.pow(hiposide, 2)- Math.pow(longElbowHand, 2))/(2*longShoulderElbow*hiposide)
var tiltShoulderAngle = Math.acos(cosA)
// move tilt shouder
var cosC=(Math.pow(longElbowHand,2)+ Math.pow(longShoulderElbow, 2)- Math.pow(hiposide, 2))/(2*longElbowHand*longShoulderElbow)
var tiltElbowAngle = Math.acos(cosC)
// move tiltElbowAngle
// CLOSE PAW 
/////////////////////////////////////////////////////////////

// Set TO HOME

/////////////////////////// Leaving ////////////////////////////
var plainDistance = Math.sqrt(Math.pow((y-ybase), 2)+Math.pow((x-xbase), 2))
var baseAngle = Math.asin((y-ybase)/plainDistance)
// move shoulder to angle in base reference
var rectSide=baseHeight - topPiece
var hiposide = Math.sqrt(Math.pow(rectSide,2)+Math.pow(plainDistance, 2))
var cosA=(Math.pow(longShoulderElbow,2)+ Math.pow(hiposide, 2)- Math.pow(longElbowHand, 2))/(2*longShoulderElbow*hiposide)
var tiltShoulderAngle = Math.acos(cosA)
// move tilt shouder
var cosC=(Math.pow(longElbowHand,2)+ Math.pow(longShoulderElbow, 2)- Math.pow(hiposide, 2))/(2*longElbowHand*longShoulderElbow)
var tiltElbowAngle = Math.acos(cosC)
// move tiltElbowAngle
// OPEN PAW 
/////////////////////////////////////////////////////////////

