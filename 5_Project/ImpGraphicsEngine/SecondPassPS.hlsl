Texture2D tex_pos : register(t0);
Texture2D tex_color : register(t1);
SamplerState gSampler : register(s0);

struct PS_INPUT
{
    float4 Position : SV_POSITION;
    float2 TexCoord : TEXCOORD;
};

float4 PS(PS_INPUT pin) : SV_Target
{
    //float4 position = tex_pos.Sample(gSampler, pin.TexCoord * 2).xyzw;
    //float4 color = tex_color.Sample(gSampler, (pin.TexCoord * 2) - float2(1.0f, 1.0f)).xyzw;
    //float4 add = tex_pos.Sample(gSampler, (pin.TexCoord * 2) - float2(1.0f, 0.0f)).xyzw * 0.5 +
    //            tex_color.Sample(gSampler, (pin.TexCoord * 2) - float2(1.0f, 0.0f)).xyzw * 0.5;
    //
    //return position * 1.0f + color * 1.0f + add * 1.0f;
    
    float4 position = tex_pos.Sample(gSampler, pin.TexCoord).xyzw;
    float4 color = tex_color.Sample(gSampler, pin.TexCoord).xyzw;
    
    //return position * 0.5f + color * 0.5f;
    //return color;
    return position;
}