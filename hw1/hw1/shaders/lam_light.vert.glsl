# version 120 


// Mine is an old machine.  For version 130 or higher, do 
// out vec4 color ;  
// out vec4 mynormal ; 
// out vec4 myvertex ;
// That is certainly more modern

varying vec4 color ; 
varying vec3 mynormal ; 
varying vec4 myvertex ; 

varying vec3 eyedirn;
varying vec3 mypos;

uniform int islight ; // are we lighting. 

//OREO
uniform vec4 lightposn[10] ;
uniform vec4 lightcolor[10] ;
uniform int lightcount ;

uniform vec4 diffuse ; 

vec4 ComputeLight (const in vec3 direction, const in vec4 lightcolor, const in vec3 norm, const in vec4 mydiffuse) {

        float nDotL = dot(norm, direction)  ;
		//float nDotL = dot(vec3(0.0), direction);         
        vec4 lambert = mydiffuse * lightcolor * max (nDotL, 0.0) ;  
        //vec4 lambert = vec4(0.0);
		return lambert ;            
}

void main() {
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex ; 
    color = gl_Color ; 
    mynormal = gl_Normal ; 
    myvertex = gl_Vertex ; 
       
    if (islight == 0) {} 
    else { 
        // They eye is always at (0,0,0) looking down -z axis 
        // Also compute current fragment position and direction to eye 

		const vec3 eyepos = vec3(0, 0, 0) ;
        vec4 _mypos = gl_ModelViewMatrix * myvertex ; 
        mypos = _mypos.xyz / _mypos.w ; // Dehomogenize current location 
        eyedirn = normalize(eyepos - mypos) ; 

        // Compute normal, needed for shading. 
        // Simpler is vec3 normal = normalize(gl_NormalMatrix * mynormal) ; 
        vec3 _normal = (gl_ModelViewMatrixInverseTranspose*vec4(mynormal,0.0)).xyz ; 
        vec3 normal = normalize(_normal) ; 

		vec3 position;
		vec3 direction;
		vec4 col0 = vec4(0.0), col1 = vec4(0.0), col2 = vec4(0.0), col3 = vec4(0.0), col4 = vec4(0.0);
		vec4 col5 = vec4(0.0), col6 = vec4(0.0), col7 = vec4(0.0), col8 = vec4(0.0), col9 = vec4(0.0);

		if (lightcount > 0) {
			vec4 thisPos = lightposn[0] ;
			vec4 thisColor = lightcolor[0] ;
			if (thisPos.w == 0) {
				direction = normalize(thisPos.xyz) ;
			} else {
				position = thisPos.xyz / thisPos.w ;
				direction = normalize(position - mypos) ;
			}
			col0 = ComputeLight(direction, thisColor, normal, diffuse) ;
		}
		if (lightcount > 1) {
			vec4 thisPos = lightposn[1] ;
			vec4 thisColor = lightcolor[1] ;
			if (thisPos.w == 0) {
				direction = normalize(thisPos.xyz) ;
			} else {
				position = thisPos.xyz / thisPos.w ;
				direction = normalize(position - mypos) ;
			}
			col1 = ComputeLight(direction, thisColor, normal, diffuse) ;
		}
		if (lightcount > 2) {
			vec4 thisPos = lightposn[2] ;
			vec4 thisColor = lightcolor[2] ;
			if (thisPos.w == 0) {
				direction = normalize(thisPos.xyz) ;
			} else {
				position = thisPos.xyz / thisPos.w ;
				direction = normalize(position - mypos) ;
			}
			col2 = ComputeLight(direction, thisColor, normal, diffuse) ;
		}
		if (lightcount > 3) {
			vec4 thisPos = lightposn[3] ;
			vec4 thisColor = lightcolor[3] ;
			if (thisPos.w == 0) {
				direction = normalize(thisPos.xyz) ;
			} else {
				position = thisPos.xyz / thisPos.w ;
				direction = normalize(position - mypos) ;
			}
			col3 = ComputeLight(direction, thisColor, normal, diffuse) ;
		}
		if (lightcount > 4) {
			vec4 thisPos = lightposn[4] ;
			vec4 thisColor = lightcolor[4] ;
			if (thisPos.w == 0) {
				direction = normalize(thisPos.xyz) ;
			} else {
				position = thisPos.xyz / thisPos.w ;
				direction = normalize(position - mypos) ;
			}
			col4 = ComputeLight(direction, thisColor, normal, diffuse) ;
		}
		if (lightcount > 5) {
			vec4 thisPos = lightposn[5] ;
			vec4 thisColor = lightcolor[5] ;
			if (thisPos.w == 0) {
				direction = normalize(thisPos.xyz) ;
			} else {
				position = thisPos.xyz / thisPos.w ;
				direction = normalize(position - mypos) ;
			}
			col5 = ComputeLight(direction, thisColor, normal, diffuse) ;
		}
		if (lightcount > 6) {
			vec4 thisPos = lightposn[6] ;
			vec4 thisColor = lightcolor[6] ;
			if (thisPos.w == 0) {
				direction = normalize(thisPos.xyz) ;
			} else {
				position = thisPos.xyz / thisPos.w ;
				direction = normalize(position - mypos) ;
			}
			col6 = ComputeLight(direction, thisColor, normal, diffuse) ;
		}
		if (lightcount > 7) {
			vec4 thisPos = lightposn[7] ;
			vec4 thisColor = lightcolor[7] ;
			if (thisPos.w == 0) {
				direction = normalize(thisPos.xyz) ;
			} else {
				position = thisPos.xyz / thisPos.w ;
				direction = normalize(position - mypos) ;
			}
			col7 = ComputeLight(direction, thisColor, normal, diffuse) ;
		}
		if (lightcount > 8) {
			vec4 thisPos = lightposn[8] ;
			vec4 thisColor = lightcolor[8] ;
			if (thisPos.w == 0) {
				direction = normalize(thisPos.xyz) ;
			} else {
				position = thisPos.xyz / thisPos.w ;
				direction = normalize(position - mypos) ;
			}
			col8 = ComputeLight(direction, thisColor, normal, diffuse) ;
		}
		if (lightcount > 9) {
			vec4 thisPos = lightposn[9] ;
			vec4 thisColor = lightcolor[9] ;
			if (thisPos.w == 0) {
				direction = normalize(thisPos.xyz) ;
			} else {
				position = thisPos.xyz / thisPos.w ;
				direction = normalize(position - mypos) ;
			}
			col9 = ComputeLight(direction, thisColor, normal, diffuse) ;
		}

        color = col0 + col1 + col2 + col3 + col4 + col5 + col6 + col7 + col8 + col9 ;
//		
        }
}
