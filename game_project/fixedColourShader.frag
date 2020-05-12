uniform sampler2D texture;

int colourMode=1;
void main()
{
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	
	vec3 v=pixel.rgb;

	//black
    if (v==(0.0,0.0,0.0))
	{
		//yellow
		if (colourMode==1)
		{
			v=vec3(1.0,1.0,0.85);
		}
		else if (colourMode==2)
		{
			v=vec3(0.949,0.878,0.741);
		}
	}
	//white
	else if (v==(1.0,1.0,1.0))
	{
		//deep pink
		//v=vec3(1.0,0.1098,0.41960);
		if (colourMode==1)
		{
			v=vec3(1.0,0.0,77.0/255.0);
		}
		else if (colourMode==2)
		{
			v=vec3(0.714,0.133,0.188);
		}
	}
	else if (v==(0.0,1.0,0.0))
	{
	if (colourMode==1)
		{
			//v=vec3(1.0,5.0/255.0,5.0/255.0);
			v=vec3(0.0,1.0,1.0);
		}
	else if (colourMode==2)
		{
			//v=vec3(0.925,0.396,0.184);
			v=vec3(0.0,1.0,1.0);
		}
		v=vec3(1.0,1.0,1.0);
	}

//	else{
//	if (colourMode==1)
//		{
//			v=vec3(1.0,0.0,77.0/255.0);
//		}
//		else if (colourMode==2)
//		{
//			v=vec3(0.714,0.133,0.188);
//		}
//	}

	

	//else if (shaderMode==1)
	//{
	//v.r=(float(int(255*(v.r*gl_TexCoord[0].x+10*1/(runTime*1.0*gl_TexCoord[0].x*gl_TexCoord[0].y)))%255)/255);
	//v.g=(float(int(10*runTime+255*(v.g*gl_TexCoord[0].y+(runTime*0.50*gl_TexCoord[0].y*gl_TexCoord[0])))%255)/255);
	//v.b=(float(int(20.0*runTime+255*(v.b*gl_TexCoord[0].x*gl_TexCoord[0].y+1/(runTime*100.0*gl_TexCoord[0].x*gl_TexCoord[0].y)))%255)/255);
	//}

    gl_FragColor =  vec4(v,1.0);
}