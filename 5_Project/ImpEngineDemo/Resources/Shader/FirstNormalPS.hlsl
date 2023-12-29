struct VertexOut
{
    float4 PosH : SV_POSITION;
    float3 Normal : NORMAL;
};

struct PixelOut
{
    float4 PosH : SV_Target0;
    float4 Normal : SV_Target1;
};

PixelOut PS(VertexOut pin)
{
    PixelOut pOut;
    
    pOut.PosH = normalize(pin.PosH);
    pOut.Normal = float4(pin.Normal.xyz, 1.0f);
    
    return pOut;
}