#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;

uniform int variable;

void main()
{

    if(variable == 3){
        FragColor = texture(texture1, TexCoord);
    }
    else if(variable == 1){
        FragColor = texture(texture2, TexCoord);
    }
    else if(variable == 2){
        FragColor = texture(texture3, TexCoord);
    }
    else{
        FragColor = texture(texture1, TexCoord);
    }

// linearly interpolate between both textures (80% container, 20% awesomeface)
//FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
//FragColor = texture(texture1, TexCoord);
}