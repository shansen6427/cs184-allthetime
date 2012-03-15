# version 120 

// Mine is an old machine.  For version 130 or higher, do 
// in vec4 color ;  
// in vec4 mynormal ; 
// in vec4 myvertex ;
// That is certainly more modern

varying vec4 color ;
varying vec3 mynormal ; 

varying vec3 eyedirn;
varying vec3 mypos;

uniform int islight ; // are we lighting. 

//OREO
uniform vec4 lightposn[10] ;
uniform vec4 lightcolor[10] ;
uniform int lightcount ;

// Now, set the material parameters.  These could be varying and/or bound to 
// a buffer.  But for now, I'll just make them uniform.  
// I use ambient, diffuse, specular, shininess as in OpenGL.  
// But, the ambient is just additive and doesn't multiply the lights.  

uniform vec4 ambient ; 
uniform vec4 specular ; 
uniform vec4 emission ;
uniform float shininess ; 

vec4 ComputeLight (const in vec4 lightcolor, const in vec3 norm, const in vec3 halfvec, const in vec4 myspecular, const in float myshininess) {

        float nDotH = dot(norm, halfvec) ; 
        vec4 phong = myspecular * lightcolor * pow (max(nDotH, 0.0), myshininess) ;  
        return phong ;            
}       

void main (void) 
{       
    if (islight == 0) gl_FragColor = color ; 
    else { 
	
        // Compute normal, needed for shading. 
        // Simpler is vec3 normal = normalize(gl_NormalMatrix * mynormal) ; 
        vec3 _normal = (gl_ModelViewMatrixInverseTranspose*vec4(mynormal,0.0)).xyz ; 
        vec3 normal = normalize(_normal) ;

		vec3 position;
		vec3 direction;
		vec3 halfAngle;
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
			halfAngle = normalize(direction + eyedirn) ;
			col0 = ComputeLight(thisColor, normal, halfAngle, specular, shininess) ;
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
			halfAngle = normalize(direction + eyedirn) ;
			col1 = ComputeLight(thisColor, normal, halfAngle, specular, shininess) ;
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
			halfAngle = normalize(direction + eyedirn) ;
			col2 = ComputeLight(thisColor, normal, halfAngle, specular, shininess) ;
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
			halfAngle = normalize(direction + eyedirn) ;
			col3 = ComputeLight(thisColor, normal, halfAngle, specular, shininess) ;
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
			halfAngle = normalize(direction + eyedirn) ;
			col4 = ComputeLight(thisColor, normal, halfAngle, specular, shininess) ;
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
			halfAngle = normalize(direction + eyedirn) ;
			col5 = ComputeLight(thisColor, normal, halfAngle, specular, shininess) ;
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
			halfAngle = normalize(direction + eyedirn) ;
			col6 = ComputeLight(thisColor, normal, halfAngle, specular, shininess) ;
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
			halfAngle = normalize(direction + eyedirn) ;
			col7 = ComputeLight(thisColor, normal, halfAngle, specular, shininess) ;
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
			halfAngle = normalize(direction + eyedirn) ;
			col8 = ComputeLight(thisColor, normal, halfAngle, specular, shininess) ;
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
			halfAngle = normalize(direction + eyedirn) ;
			col9 = ComputeLight(thisColor, normal, halfAngle, specular, shininess) ;
		}

	        gl_FragColor = color + ambient + emission + col0 + col1 + col2 + col3 + col4 + col5 + col6 + col7 + col8 + col9 ;
		
        }
}
