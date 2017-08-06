highp    attribute vec4 vertex;
highp    attribute vec3 normal;
highp    uniform mat4 projMatrix;
highp    uniform mat4 mvMatrix;
highp    uniform mat3 normalMatrix;
highp    varying vec2  texCoord;
highp    float  Pi=3.1415926;
     void main() {   

        highp vec3  rvertex=normalMatrix*vertex.xyz;
         texCoord.y=asin(rvertex.y)/Pi+0.5;
        highp float len=sqrt( pow(rvertex.x,2)+pow(rvertex.z,2));
         if(rvertex.z>=0.0){
                texCoord.x=acos(rvertex.x/len)/Pi/2.0;
         }
         else{
                texCoord.x=-acos(rvertex.x/len)/Pi/2.0+1.0;
         }

        gl_Position = projMatrix * mvMatrix * vertex;
     }   
