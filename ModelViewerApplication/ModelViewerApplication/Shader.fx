//--------------------------------------------------------------------------------------
// File: Tutorial02.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

Texture2D faceTexture;
Texture2D skyboxTexture;
Texture2D normalFaceTexture;
Texture2D houseTexture;
Texture2D normalHouseTexture;

SamplerState anisoSampler {
	Filter = ANISOTROPIC;
};

cbuffer cWorldViewProj {
	float4x4 gWVP;
	float4x4 worldInvTrans;
	float4x4 worldMatrix;

	float4 diffuseMaterial;
	float4 diffuseLight;

	float3 lightVector;
	float4 ambientLightColor;

	float4 specularMaterial; 
	float4 specularLight; 
	float specularPower; 
	float3 eyePos;
};

struct bumpVOut {
	float4 position : SV_POSITION;
	float2 textureCoord : TEXCOORD;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
};


struct textureVOut {
	float4 position : SV_POSITION;
	float2 textureCoord : TEXCOORD;
	float3 normal : NORMAL;
	float4 vPosition : POSITION;
};

struct vOut {
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float3 normal : NORMAL;
};



//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
vOut VS( float4 pos : POSITION , float4 color : COLOR, float3 norm : NORMAL)
{
	vOut output;
	float3 normal;

	output.position = mul(pos, gWVP);

	normal = mul(norm, gWVP);

	//normal = mul(float4(norm, 0.0f), worldInvTrans).xyz;
	
	output.normal = normalize(normal);
	
	output.color = color;

    return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( float4 pos : SV_POSITION , float4 color : COLOR, float3 norm : NORMAL) : SV_Target
{
	float4 finalColor;
	float4 diffuseColor;
	float4 ambientColor;
	float4 specColor;

	norm = normalize(norm);

	//angle for diffuse lighting
	float angle = max(dot(lightVector, norm), 0.0f);

	//viewing direction
	float3 toEye = normalize(eyePos - pos); 

	// Compute the reflection vector.
	float3 r = reflect(lightVector, norm);

	//// Determine how much (if any) specular light makes it into the eye.
	float t = pow(max(dot(toEye, r), 0.0f), specularPower);

	//// Compute the ambient, diffuse, and specular terms separately. 
	specColor = t*( specularMaterial * specularLight );

	diffuseColor = angle*(diffuseMaterial * diffuseLight);
	
	ambientColor = color * ambientLightColor;

	finalColor = diffuseColor + ambientColor + specColor;
	
	finalColor.a = diffuseMaterial.a;

	return finalColor;

	
	/* ambient and diffuse
	float angle = max(dot(lightVector, norm), 0);

	float4 finalColor;
	float4 diffuseColor;
	float4 ambientColor;

	diffuseColor = angle*(diffuseMaterial * diffuseLight);
	
	ambientColor = color * ambientLightColor;

	finalColor = ambientColor + diffuseColor + spec;
	
	finalColor.a = diffuseMaterial.a;

	return finalColor;
	*/


	/* OLD
	float3 triNormal = {0.0f, 0.0f, 1.0f};
	float3 lightDirection = {0.0f, 0.0f, 1.0f};

	float4 triColor = color;
	float4 lightColor = {1.0f, 1.0f, 1.0f, 1.0f};

	float finalDirection = dot(triNormal, lightDirection);

	//float4 finalColor = triColor * lightColor;

	float4 finalOutput = finalColor * finalDirection;

	return finalOutput;
	*/

}

//--------------------------------------------------------------------------------------
// Texture Vertex Shader
//--------------------------------------------------------------------------------------
textureVOut textureVS( float4 pos : POSITION , float2 tex : TEXCOORD, float3 norm : NORMAL)
{
	textureVOut output;

	output.position = mul(pos, gWVP);

	output.vPosition = mul(pos, worldMatrix);

	//output.normal = mul(norm, worldInvTrans);

	output.normal = norm;

	output.textureCoord = tex;

    return output;
}

//--------------------------------------------------------------------------------------
// Texture Pixel Shader
//--------------------------------------------------------------------------------------
float4 texturePS( float4 pos : SV_POSITION , float2 tex : TEXCOORD, float3 norm : NORMAL, float4 vPos : POSITION) : SV_Target
{

	float4 color = faceTexture.Sample(anisoSampler, tex); 

	float angle = max(dot(lightVector, norm), 0.0f);
		
	float3 toEye = normalize(eyePos - vPos); 
		
	// Compute Colour
	// Compute the reflection vector.
	float3 r = reflect(lightVector, norm);

	//// Determine how much (if any) specular light makes it into the eye.
	float t = pow(max(dot(r, toEye), 0.0f), specularPower);

	//// Compute the ambient, diffuse, and specular terms separately. 
	float4 spec = t*(specularMaterial * specularLight);

	float4 finalColor;
	float4 diffuseColor;
	float4 ambientColor;

	diffuseColor = angle*(diffuseMaterial * diffuseLight);
	
	ambientColor = color * ambientLightColor;

	finalColor = ambientColor + diffuseColor + spec;
	
	finalColor.a = diffuseMaterial.a;

	//return diffuseColor;

	return finalColor;
	
	
	/*
	float4 texColor = faceTexture.Sample(anisoSampler, tex); 

	float3 triNormal = {0.0f, 0.0f, 1.0f};
	float3 lightDirection = {0.0f, 0.0f, 1.0f};
	
	float4 triColor = texColor;
	float4 lightColor = {1.0f, 1.0f, 1.0f, 1.0f};

	float finalDirection = dot(triNormal, lightDirection);

	float4 finalColor = triColor * lightColor;

	float4 finalOutput = finalColor * finalDirection;

	return finalOutput;
	*/
}

//--------------------------------------------------------------------------------------
// Skybox Vertex Shader
//--------------------------------------------------------------------------------------
textureVOut skyboxVS( float4 pos : POSITION , float2 tex : TEXCOORD, float3 norm : NORMAL)
{
	textureVOut output;

	output.position = mul(pos, gWVP);

	output.normal = normalize(norm);

	output.textureCoord = tex;

    return output;
}

//--------------------------------------------------------------------------------------
// Skybox Pixel Shader
//--------------------------------------------------------------------------------------
float4 skyboxPS( float4 pos : SV_POSITION , float2 tex : TEXCOORD, float3 norm : NORMAL) : SV_Target
{
	
	float4 texColor = skyboxTexture.Sample(anisoSampler, tex); 

	float3 triNormal = {0.0f, 0.0f, 1.0f};
	float3 lightDirection = {0.0f, 0.0f, 1.0f};
	
	float4 triColor = texColor;
	float4 lightColor = {1.0f, 1.0f, 1.0f, 1.0f};

	float finalDirection = dot(triNormal, lightDirection);

	float4 finalColor = triColor * lightColor;

	float4 finalOutput = finalColor * finalDirection;

	return finalOutput;
	
}

//--------------------------------------------------------------------------------------
// Bump Vertex Shader
//--------------------------------------------------------------------------------------
bumpVOut bumpVS( float4 pos : POSITION , float2 tex : TEXCOORD, float3 norm : NORMAL, float3 tang : TANGENT)
{
	bumpVOut output;

	output.position = mul(pos, gWVP);

	output.normal = (norm);

	output.tangent = (tang);

	output.textureCoord = tex;

    return output;
}

//--------------------------------------------------------------------------------------
// Bump Pixel Shader
//--------------------------------------------------------------------------------------
float4 bumpPS( float4 pos : SV_POSITION , float2 tex : TEXCOORD, float3 norm : NORMAL, float3 tang : TANGENT) : SV_Target
{
	
	float4 color = faceTexture.Sample(anisoSampler, tex); 
	float4 normal = normalFaceTexture.Sample(anisoSampler, tex);

	float3 lightDirect = normalize(lightVector);

	float3 toEye = normalize(eyePos - pos); 

	//Bump mapping 
	//Building TBN matrix
	float3 T = tang;
	float3 N = norm;
	float3 B = cross(tang, norm);

	float3x3 TBN = float3x3(T, B, N);

	//Transform form world space to tangent space. ts = tangent space
	float3 tsNormal = mul(normal, TBN);
	float3 tsEye = mul(toEye, TBN);
	float3 tsLight = mul(lightDirect, TBN);




	float angle = max(dot(tsLight, tsNormal), 0.0f);
	
	// Compute Colour
	// Compute the reflection vector.
	float3 r = reflect(tsLight, tsNormal);

	//// Determine how much (if any) specular light makes it into the eye.
	float t = pow(max(dot(tsEye, r), 0.0f), specularPower);

	//// Compute the ambient, diffuse, and specular terms separately. 
	float4 spec = t*(specularMaterial * specularLight);

	float4 finalColor;
	float4 diffuseColor;
	float4 ambientColor;

	diffuseColor = angle*(diffuseMaterial * diffuseLight);
	
	ambientColor = color * ambientLightColor;

	finalColor = ambientColor + diffuseColor + spec;
	
	finalColor.a = diffuseMaterial.a;

	//return diffuseColor;

	return finalColor;
	
}

//--------------------------------------------------------------------------------------
// House Vertex Shader
//--------------------------------------------------------------------------------------
bumpVOut houseVS( float4 pos : POSITION , float2 tex : TEXCOORD, float3 norm : NORMAL, float3 tang : TANGENT)
{
	bumpVOut output;

	output.position = mul(pos, gWVP);

	output.normal = (norm);

	output.tangent = (tang);

	output.textureCoord = tex;

    return output;
}

//--------------------------------------------------------------------------------------
// House Pixel Shader
//--------------------------------------------------------------------------------------
float4 housePS( float4 pos : SV_POSITION , float2 tex : TEXCOORD, float3 norm : NORMAL, float3 tang : TANGENT) : SV_Target
{
	
	float4 color = houseTexture.Sample(anisoSampler, tex); 
	float4 normal = normalHouseTexture.Sample(anisoSampler, tex);

	float3 toEye = normalize(eyePos - pos); 
	float3 lightDirect = normalize(lightVector);

	//Bump mapping 
	//Building TBN matrix
	float3 T = tang;
	float3 N = norm;
	float3 B = cross(tang, norm);

	float3x3 TBN = float3x3(T, B, N);

	//Transform form world space to tangent space. ts = tangent space
	float3 tsNormal = mul(normal, TBN);
	float3 tsEye = mul(toEye, TBN);
	float3 tsLight = mul(lightDirect, TBN);

	float angle = max(dot(tsLight, tsNormal), 0.0f);
	
	// Compute Colour
	// Compute the reflection vector.
	float3 r = reflect(tsLight, tsNormal);

	//// Determine how much (if any) specular light makes it into the eye.
	float t = pow(max(dot(tsEye, r), 0.0f), specularPower);

	//// Compute the ambient, diffuse, and specular terms separately. 
	float4 spec = t*(specularMaterial * specularLight);

	float4 finalColor;
	float4 diffuseColor;
	float4 ambientColor;

	diffuseColor = angle*(diffuseMaterial * diffuseLight);
	
	ambientColor = color * ambientLightColor;

	finalColor = ambientColor + diffuseColor + spec;
	
	finalColor.a = diffuseMaterial.a;

	//return diffuseColor;

	return finalColor;
	
}
technique11 Tech {
	pass P0 {
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
}

technique11 textureTech {
	pass P0 {
		SetVertexShader(CompileShader(vs_5_0, textureVS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, texturePS()));
	}
}

technique11 skyboxTech {
	pass P0 {
		SetVertexShader(CompileShader(vs_5_0, skyboxVS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, skyboxPS()));
	}
}

technique11 bumpTech {
	pass P0 {
		SetVertexShader(CompileShader(vs_5_0, bumpVS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, bumpPS()));
	}
}

technique11 houseTech {
	pass P0 {
		SetVertexShader(CompileShader(vs_5_0, houseVS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, housePS()));
	}
}