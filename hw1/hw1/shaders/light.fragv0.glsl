# version 120 

// Mine is an old machine.  For version 130 or higher, do 
// in vec4 color ;  
// in vec4 mynormal ; 
// in vec4 myvertex ;
// That is certainly more modern

varying vec4 color ;
varying vec3 mynormal ; 
varying vec4 myvertex ; 

uniform int islight ; // are we lighting. 

// Assume light 0 and light 1 are both point lights
// The actual light values are passed from the main OpenGL program. 
// This could of course be fancier.  My goal is to illustrate a simple idea. 

uniform vec4 light0posn ; 
uniform vec4 light0color ; 
uniform vec4 light1posn ; 
uniform vec4 light1color ;
uniform vec4 light2posn ; 
uniform vec4 light2color ; 
uniform vec4 light3posn ; 
uniform vec4 light3color ;
uniform vec4 light4posn ; 
uniform vec4 light4color ; 
uniform vec4 light5posn ; 
uniform vec4 light5color ;
uniform vec4 light6posn ; 
uniform vec4 light6color ; 
uniform vec4 light7posn ; 
uniform vec4 light7color ;
uniform vec4 light8posn ; 
uniform vec4 light8color ; 
uniform vec4 light9posn ; 
uniform vec4 light9color ;

//uniform vec4 lightsposn[10];
//uniform vec4 lightscolor[10];
uniform int num_lights;

// Now, set the material parameters.  These could be varying and/or bound to 
// a buffer.  But for now, I'll just make them uniform.  
// I use ambient, diffuse, specular, shininess as in OpenGL.  
// But, the ambient is just additive and doesn't multiply the lights.  

uniform vec4 ambient ; 
uniform vec4 diffuse ; 
uniform vec4 specular ; 
uniform vec4 emission ;
uniform float shininess ; 

vec4 ComputeLight (const in vec3 direction, const in vec4 lightcolor, const in vec3 normal, const in vec3 halfvec, const in vec4 mydiffuse, const in vec4 myspecular, const in float myshininess) {

        float nDotL = dot(normal, direction)  ;         
        vec4 lambert = mydiffuse * lightcolor * max (nDotL, 0.0) ;  

        float nDotH = dot(normal, halfvec) ; 
        vec4 phong = myspecular * lightcolor * pow (max(nDotH, 0.0), myshininess) ; 

        vec4 retval = lambert + phong ; 
        return retval ;            
}       

void main (void) 
{       
    if (islight == 0) gl_FragColor = color ; 
    else { 
        // They eye is always at (0,0,0) looking down -z axis 
        // Also compute current fragment position and direction to eye 

        const vec3 eyepos = vec3(0,0,0) ; 
        vec4 _mypos = gl_ModelViewMatrix * myvertex ; 
        vec3 mypos = _mypos.xyz / _mypos.w ; // Dehomogenize current location 
        vec3 eyedirn = normalize(eyepos - mypos) ; 

        // Compute normal, needed for shading. 
        // Simpler is vec3 normal = normalize(gl_NormalMatrix * mynormal) ; 
        vec3 _normal = (gl_ModelViewMatrixInverseTranspose*vec4(mynormal,0.0)).xyz ; 
        vec3 normal = normalize(_normal) ; 

        // Light 0, point
        //vec3 position0 = light0posn.xyz / light0posn.w ; 
        //vec3 direction0 = normalize (position0 - mypos) ; // no attenuation 
        //vec3 half0 = normalize (direction0 + eyedirn) ;  
        //vec4 col0 = ComputeLight(direction0, light0color, normal, half0, diffuse, specular, shininess) ;

        // Light 1, point 
        //vec3 position1 = light1posn.xyz / light1posn.w ; 
        //vec3 direction1 = normalize (position1 - mypos) ; // no attenuation 
        //vec3 half1 = normalize (direction1 + eyedirn) ;  
        //vec4 col1 = ComputeLight(direction1, light1color, normal, half1, diffuse, specular, shininess) ;
        
        //gl_FragColor = ambient + col0 + col1 ;
	
		vec3 position;
		vec3 direction;
		vec3 halfvec;
		vec4 col0 = vec4(0.0), col1 = vec4(0.0), col2 = vec4(0.0), col3 = vec4(0.0), col4 = vec4(0.0);
		vec4 col5 = vec4(0.0), col6 = vec4(0.0), col7 = vec4(0.0), col8 = vec4(0.0), col9 = vec4(0.0);

		if(num_lights > 0){
			position = light0posn.xyz / light0posn.w ; 
			direction = normalize (position - mypos) ; // no attenuation 
			halfvec = normalize (direction + eyedirn) ;  
			col0 = ComputeLight(direction, light0color, normal, halfvec, diffuse, specular, shininess) ;
		}
		if(num_lights > 1){
			position = light1posn.xyz / light1posn.w ; 
			direction = normalize (position - mypos) ; // no attenuation 
			halfvec = normalize (direction + eyedirn) ;  
			col1 = ComputeLight(direction, light1color, normal, halfvec, diffuse, specular, shininess) ;
		}
		if(num_lights > 2){
			position = light2posn.xyz / light2posn.w ; 
			direction = normalize (position - mypos) ; // no attenuation 
			halfvec = normalize (direction + eyedirn) ;  
			col2 = ComputeLight(direction, light2color, normal, halfvec, diffuse, specular, shininess) ;
		}
		if(num_lights > 3){
			position = light3posn.xyz / light3posn.w ; 
			direction = normalize (position - mypos) ; // no attenuation 
			halfvec = normalize (direction + eyedirn) ;  
			col3 = ComputeLight(direction, light3color, normal, halfvec, diffuse, specular, shininess) ;
		}
		if(num_lights > 4){
			position = light4posn.xyz / light4posn.w ; 
			direction = normalize (position - mypos) ; // no attenuation 
			halfvec = normalize (direction + eyedirn) ;  
			col4 = ComputeLight(direction, light4color, normal, halfvec, diffuse, specular, shininess) ;
		}
		if(num_lights > 5){
			position = light5posn.xyz / light5posn.w ; 
			direction = normalize (position - mypos) ; // no attenuation 
			halfvec = normalize (direction + eyedirn) ;  
			col5 = ComputeLight(direction, light5color, normal, halfvec, diffuse, specular, shininess) ;
		}
		if(num_lights > 6){
			position = light6posn.xyz / light6posn.w ; 
			direction = normalize (position - mypos) ; // no attenuation 
			halfvec = normalize (direction + eyedirn) ;  
			col6 = ComputeLight(direction, light6color, normal, halfvec, diffuse, specular, shininess) ;
		}
		if(num_lights > 7){
			position = light7posn.xyz / light7posn.w ; 
			direction = normalize (position - mypos) ; // no attenuation 
			halfvec = normalize (direction + eyedirn) ;  
			col7 = ComputeLight(direction, light7color, normal, halfvec, diffuse, specular, shininess) ;
		}
		if(num_lights > 8){
			position = light8posn.xyz / light8posn.w ; 
			direction = normalize (position - mypos) ; // no attenuation 
			halfvec = normalize (direction + eyedirn) ;  
			col8 = ComputeLight(direction, light8color, normal, halfvec, diffuse, specular, shininess) ;
		}
		if(num_lights > 9){
			position = light9posn.xyz / light9posn.w ; 
			direction = normalize (position - mypos) ; // no attenuation 
			halfvec = normalize (direction + eyedirn) ;  
			col9 = ComputeLight(direction, light9color, normal, halfvec, diffuse, specular, shininess) ;
		}

		gl_FragColor = ambient + emission + col0 + col1 + col2 + col3 + col4 + col5 + col6 + col7 + col8 + col9;
        }
}
