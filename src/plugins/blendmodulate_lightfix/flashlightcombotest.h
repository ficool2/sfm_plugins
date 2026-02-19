// ALL SKIP STATEMENTS THAT AFFECT THIS SHADER!!!
// !$WORLDVERTEXTRANSITION && $NORMALMAP2
// !$NORMALMAP && $NORMALMAP2
// !$DETAILTEXTURE && ( $DETAIL_BLEND_MODE != 0 )
// defined $PIXELFOGTYPE && defined $WRITEWATERFOGTODESTALPHA && ( $PIXELFOGTYPE != 1 ) && $WRITEWATERFOGTODESTALPHA
// defined $LIGHTING_PREVIEW && defined $FASTPATHENVMAPTINT && $LIGHTING_PREVIEW && $FASTPATHENVMAPTINT
// defined $LIGHTING_PREVIEW && defined $FASTPATHENVMAPCONTRAST && $LIGHTING_PREVIEW && $FASTPATHENVMAPCONTRAST
// defined $LIGHTING_PREVIEW && defined $FASTPATH && $LIGHTING_PREVIEW && $FASTPATH
// ($FLASHLIGHT || $FLASHLIGHTSHADOWS) && $LIGHTING_PREVIEW
// defined $PIXELFOGTYPE && defined $WRITEWATERFOGTODESTALPHA && ( $PIXELFOGTYPE != 1 ) && $WRITEWATERFOGTODESTALPHA
// defined $LIGHTING_PREVIEW && defined $FASTPATHENVMAPTINT && $LIGHTING_PREVIEW && $FASTPATHENVMAPTINT
// defined $LIGHTING_PREVIEW && defined $FASTPATHENVMAPCONTRAST && $LIGHTING_PREVIEW && $FASTPATHENVMAPCONTRAST
// defined $LIGHTING_PREVIEW && defined $FASTPATH && $LIGHTING_PREVIEW && $FASTPATH
// ($FLASHLIGHT || $FLASHLIGHTSHADOWS) && $LIGHTING_PREVIEW
// $FANCY_BLENDING && !$WORLDVERTEXTRANSITION

#pragma once

// ficool2: stubs
#define Assert( x )
#define AssertMsg( x, msg )

#define MATERIAL_VAR_VERTEXFOG (1 << 31)
#define IS_FLAG_SET( flag ) rand()

class flashlight_ps30_MOD_Static_Index
{
	unsigned int m_nNORMALMAP;//: 2;
	unsigned int m_nNORMALMAP2;// : 2;
	unsigned int m_nWORLDVERTEXTRANSITION;// : 2;
	unsigned int m_nSEAMLESS;// : 2;
	unsigned int m_nDETAILTEXTURE;// : 2;
	unsigned int m_nDETAIL_BLEND_MODE;// : 4;
	unsigned int m_nFLASHLIGHTDEPTHFILTERMODE;//: 2;
	unsigned int m_nDOPIXELFOG;// : 2;
	unsigned int m_nFANCY_BLENDING;// : 2;
#ifdef _DEBUG
	bool m_bNORMALMAP : 1;
	bool m_bNORMALMAP2 : 1;
	bool m_bWORLDVERTEXTRANSITION : 1;
	bool m_bSEAMLESS : 1;
	bool m_bDETAILTEXTURE : 1;
	bool m_bDETAIL_BLEND_MODE : 1;
	bool m_bFLASHLIGHTDEPTHFILTERMODE : 1;
	bool m_bFANCY_BLENDING : 1;
#endif	// _DEBUG
public:
	void SetNORMALMAP( int i )
	{
		Assert( i >= 0 && i <= 2 );
		m_nNORMALMAP = i;
#ifdef _DEBUG
		m_bNORMALMAP = true;
#endif	// _DEBUG
	}

	void SetNORMALMAP2( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nNORMALMAP2 = i;
#ifdef _DEBUG
		m_bNORMALMAP2 = true;
#endif	// _DEBUG
	}

	void SetWORLDVERTEXTRANSITION( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nWORLDVERTEXTRANSITION = i;
#ifdef _DEBUG
		m_bWORLDVERTEXTRANSITION = true;
#endif	// _DEBUG
	}

	void SetSEAMLESS( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nSEAMLESS = i;
#ifdef _DEBUG
		m_bSEAMLESS = true;
#endif	// _DEBUG
	}

	void SetDETAILTEXTURE( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nDETAILTEXTURE = i;
#ifdef _DEBUG
		m_bDETAILTEXTURE = true;
#endif	// _DEBUG
	}

	void SetDETAIL_BLEND_MODE( int i )
	{
		Assert( i >= 0 && i <= 11 );
		m_nDETAIL_BLEND_MODE = i;
#ifdef _DEBUG
		m_bDETAIL_BLEND_MODE = true;
#endif	// _DEBUG
	}

	void SetFLASHLIGHTDEPTHFILTERMODE( int i )
	{
		Assert( i >= 0 && i <= 2 );
		m_nFLASHLIGHTDEPTHFILTERMODE = i;
#ifdef _DEBUG
		m_bFLASHLIGHTDEPTHFILTERMODE = true;
#endif	// _DEBUG
	}

	void SetDOPIXELFOG( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nDOPIXELFOG = i;
	}

	void SetFANCY_BLENDING( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nFANCY_BLENDING = i;
#ifdef _DEBUG
		m_bFANCY_BLENDING = true;
#endif	// _DEBUG
	}

	flashlight_ps30_MOD_Static_Index()
	{
		m_nNORMALMAP = 0;
		m_nNORMALMAP2 = 0;
		m_nWORLDVERTEXTRANSITION = 0;
		m_nSEAMLESS = 0;
		m_nDETAILTEXTURE = 0;
		m_nDETAIL_BLEND_MODE = 0;
		m_nFLASHLIGHTDEPTHFILTERMODE = 0;
		m_nDOPIXELFOG = !IS_FLAG_SET( MATERIAL_VAR_VERTEXFOG ) ? 1 : 0;
		m_nFANCY_BLENDING = 0;
#ifdef _DEBUG
		m_bNORMALMAP = false;
		m_bNORMALMAP2 = false;
		m_bWORLDVERTEXTRANSITION = false;
		m_bSEAMLESS = false;
		m_bDETAILTEXTURE = false;
		m_bDETAIL_BLEND_MODE = false;
		m_bFLASHLIGHTDEPTHFILTERMODE = false;
		m_bFANCY_BLENDING = false;
#endif	// _DEBUG
	}

	int GetIndex() const
	{
		Assert( m_bNORMALMAP && m_bNORMALMAP2 && m_bWORLDVERTEXTRANSITION && m_bSEAMLESS && m_bDETAILTEXTURE && m_bDETAIL_BLEND_MODE && m_bFLASHLIGHTDEPTHFILTERMODE && m_bFANCY_BLENDING );
		AssertMsg( !( !m_nWORLDVERTEXTRANSITION && m_nNORMALMAP2 ), "Invalid combo combination ( !WORLDVERTEXTRANSITION && NORMALMAP2 )" );
		AssertMsg( !( !m_nNORMALMAP && m_nNORMALMAP2 ), "Invalid combo combination ( !NORMALMAP && NORMALMAP2 )" );
		AssertMsg( !( !m_nDETAILTEXTURE && ( m_nDETAIL_BLEND_MODE != 0 ) ), "Invalid combo combination ( !DETAILTEXTURE && ( DETAIL_BLEND_MODE != 0 ) )" );
		AssertMsg( !( m_nFANCY_BLENDING && !m_nWORLDVERTEXTRANSITION ), "Invalid combo combination ( FANCY_BLENDING && !WORLDVERTEXTRANSITION )" );
		return ( 8 * m_nNORMALMAP ) + ( 24 * m_nNORMALMAP2 ) + ( 48 * m_nWORLDVERTEXTRANSITION ) + ( 96 * m_nSEAMLESS ) + ( 192 * m_nDETAILTEXTURE ) + ( 384 * m_nDETAIL_BLEND_MODE ) + ( 4608 * m_nFLASHLIGHTDEPTHFILTERMODE ) + ( 13824 * m_nDOPIXELFOG ) + ( 27648 * m_nFANCY_BLENDING ) + 0;
	}
};

class flashlight_ps30_SFM_Static_Index
{
	unsigned int m_nNORMALMAP;// : 2;
	unsigned int m_nNORMALMAP2;// : 2;
	unsigned int m_nWORLDVERTEXTRANSITION;// : 2;
	unsigned int m_nSEAMLESS;// : 2;
	unsigned int m_nDETAILTEXTURE;// : 2;
	unsigned int m_nDETAIL_BLEND_MODE;// : 4;
	unsigned int m_nFLASHLIGHTDEPTHFILTERMODE;// : 2;
	unsigned int m_nDOPIXELFOG;// : 2;
#ifdef _DEBUG
	bool m_bNORMALMAP : 1;
	bool m_bNORMALMAP2 : 1;
	bool m_bWORLDVERTEXTRANSITION : 1;
	bool m_bSEAMLESS : 1;
	bool m_bDETAILTEXTURE : 1;
	bool m_bDETAIL_BLEND_MODE : 1;
	bool m_bFLASHLIGHTDEPTHFILTERMODE : 1;
#endif	// _DEBUG
public:
	void SetNORMALMAP( int i )
	{
		Assert( i >= 0 && i <= 2 );
		m_nNORMALMAP = i;
#ifdef _DEBUG
		m_bNORMALMAP = true;
#endif	// _DEBUG
	}

	void SetNORMALMAP2( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nNORMALMAP2 = i;
#ifdef _DEBUG
		m_bNORMALMAP2 = true;
#endif	// _DEBUG
	}

	void SetWORLDVERTEXTRANSITION( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nWORLDVERTEXTRANSITION = i;
#ifdef _DEBUG
		m_bWORLDVERTEXTRANSITION = true;
#endif	// _DEBUG
	}

	void SetSEAMLESS( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nSEAMLESS = i;
#ifdef _DEBUG
		m_bSEAMLESS = true;
#endif	// _DEBUG
	}

	void SetDETAILTEXTURE( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nDETAILTEXTURE = i;
#ifdef _DEBUG
		m_bDETAILTEXTURE = true;
#endif	// _DEBUG
	}

	void SetDETAIL_BLEND_MODE( int i )
	{
		Assert( i >= 0 && i <= 11 );
		m_nDETAIL_BLEND_MODE = i;
#ifdef _DEBUG
		m_bDETAIL_BLEND_MODE = true;
#endif	// _DEBUG
	}

	void SetFLASHLIGHTDEPTHFILTERMODE( int i )
	{
		Assert( i >= 0 && i <= 2 );
		m_nFLASHLIGHTDEPTHFILTERMODE = i;
#ifdef _DEBUG
		m_bFLASHLIGHTDEPTHFILTERMODE = true;
#endif	// _DEBUG
	}

	void SetDOPIXELFOG( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nDOPIXELFOG = i;
	}

	flashlight_ps30_SFM_Static_Index()
	{
		m_nNORMALMAP = 0;
		m_nNORMALMAP2 = 0;
		m_nWORLDVERTEXTRANSITION = 0;
		m_nSEAMLESS = 0;
		m_nDETAILTEXTURE = 0;
		m_nDETAIL_BLEND_MODE = 0;
		m_nFLASHLIGHTDEPTHFILTERMODE = 0;
		m_nDOPIXELFOG = !IS_FLAG_SET( MATERIAL_VAR_VERTEXFOG ) ? 1 : 0;
#ifdef _DEBUG
		m_bNORMALMAP = false;
		m_bNORMALMAP2 = false;
		m_bWORLDVERTEXTRANSITION = false;
		m_bSEAMLESS = false;
		m_bDETAILTEXTURE = false;
		m_bDETAIL_BLEND_MODE = false;
		m_bFLASHLIGHTDEPTHFILTERMODE = false;
#endif	// _DEBUG
	}

	int GetIndex() const
	{
		Assert( m_bNORMALMAP && m_bNORMALMAP2 && m_bWORLDVERTEXTRANSITION && m_bSEAMLESS && m_bDETAILTEXTURE && m_bDETAIL_BLEND_MODE && m_bFLASHLIGHTDEPTHFILTERMODE );
		AssertMsg( !( !m_nWORLDVERTEXTRANSITION && m_nNORMALMAP2 ), "Invalid combo combination ( !WORLDVERTEXTRANSITION && NORMALMAP2 )" );
		AssertMsg( !( !m_nNORMALMAP && m_nNORMALMAP2 ), "Invalid combo combination ( !NORMALMAP && NORMALMAP2 )" );
		AssertMsg( !( !m_nDETAILTEXTURE && ( m_nDETAIL_BLEND_MODE != 0 ) ), "Invalid combo combination ( !DETAILTEXTURE && ( DETAIL_BLEND_MODE != 0 ) )" );
		return ( 8 * m_nNORMALMAP ) + ( 24 * m_nNORMALMAP2 ) + ( 48 * m_nWORLDVERTEXTRANSITION ) + ( 96 * m_nSEAMLESS ) + ( 192 * m_nDETAILTEXTURE ) + ( 384 * m_nDETAIL_BLEND_MODE ) + ( 4608 * m_nFLASHLIGHTDEPTHFILTERMODE ) + ( 13824 * m_nDOPIXELFOG ) + 0;
	}
};