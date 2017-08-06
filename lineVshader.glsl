attribute vec4 Vertex;
attribute float ratio;

uniform mat4 MVP;
uniform bool colorIsOn;
uniform bool isCoordinates;
varying vec4 color;

void main(void)
{
    gl_Position = MVP* Vertex;

    if(isCoordinates){
            if(colorIsOn){
        color.xyz=normalize(abs(Vertex.xyz));
            }
            else{
        color=vec4(0.1,0.1,0.1,1.0);

            }
    }
    else{
            if(colorIsOn){
                    color.xyz=ratio*normalize(abs(Vertex.xyz));
            }
            else{
                    color=vec4(0.1,0.1,0.1,1.0);
            }
    }
}
