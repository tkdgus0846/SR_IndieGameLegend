//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "CameraFilterPack/AAA_WaterDropPro" {
Properties {
_MainTex ("Base (RGB)", 2D) = "white" { }
_MainTex2 ("Base (RGB)", 2D) = "white" { }
_TimeX ("Time", Range(0, 1)) = 1
_SizeX ("SizeX", Range(0, 1)) = 1
_SizeY ("SizeY", Range(0, 1)) = 1
_Speed ("Speed", Range(0, 10)) = 1
_Distortion ("_Distortion", Range(0, 1)) = 0.87
_ScreenResolution ("_ScreenResolution", Vector) = (0,0,0,0)
}
SubShader {
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 51467
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
}
}
}
}