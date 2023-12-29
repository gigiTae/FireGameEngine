struct VertexOut
{
    float4 PosH : SV_POSITION;
    float4 Color : COLOR;
    float2 Tex : TEXCOORD;
};

struct PixelOut
{
    float4 PosH  : SV_Target0;
    float4 Color : SV_Target1;
};

PixelOut PS(VertexOut pin)
{
    PixelOut pOut;
    
    pOut.PosH = normalize(pin.PosH);
    pOut.Color = float4(pin.Color.xyz, pin.PosH.z / pin.PosH.w);
    
    return pOut;
}