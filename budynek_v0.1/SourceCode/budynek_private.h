
// Pooled Parameter (Mixed Expressions)
//  Referenced by:
//    '<S1>/Discrete-Time Integrator'
//    '<S2>/Discrete-Time Integrator'
//    '<S3>/Filter'
//    '<S3>/Integrator'
//    '<S3>/Saturate'

#define rtCP_pooled1                   (1.0)



////////////////////////////////////////////////////////
///////////////Symulacja Budynku////////////////////////
////////////////////////////////////////////////////////

/////PID


// Expression: P
//  Referenced by: '<S3>/Proportional Gain'
#define rtCP_ProportionalGain_Gain     (0.0163422881219694)
// Expression: D
//  Referenced by: '<S3>/Derivative Gain'
#define rtCP_DerivativeGain_Gain       (3.00281069092761)
// Expression: I
//  Referenced by: '<S3>/Integral Gain'
#define rtCP_IntegralGain_Gain         (1.56457009921868E-5)
// Expression: N
//  Referenced by: '<S3>/Filter Coefficient'
#define rtCP_FilterCoefficient_Gain    (0.0136505654994395)








////////////////////////////////////////////////////////
//////////////////// Budynek ///////////////////////////
////////////////////////////////////////////////////////
// Expression: 20
//  Referenced by: '<S1>/Discrete-Time Integrator' <- Model Budynku Discrete-Time-Integrator, initial value
//
#define rtCP_DiscreteTimeIntegrator_IC (20.0)	


// Expression: k_ext
//  Referenced by: '<S1>/Gain1'
#define rtCP_Gain1_Gain                (15000.0)


// Pooled Parameter (Expression: 1/(m_b*c_b))
//  Referenced by:
//    '<S1>/Gain'
//    '<S1>/Gain3'
#define rtCP_pooled2                   (5.0E-8)







// Pooled Parameter (Mixed Expressions)
//  Referenced by:
//    '<S2>/Discrete-Time Integrator'
//    '<S3>/Filter'
//    '<S3>/Integrator'
//    '<S3>/Saturate'

#define T_PCO_initial_value                   (0.0)


// Expression: ro*c_w
//  Referenced by: '<S2>/Gain1'

#define rtCP_Gain1_Gain_h              (4.2E+6)

// Pooled Parameter (Expression: k_h)
//  Referenced by:
//    '<S1>/Gain2'
//    '<S2>/Gain2'

#define rtCP_pooled4                   (12000.0)

// Pooled Parameter (Expression: 1/(m_h*c_h))
//  Referenced by:
//    '<S2>/Gain3'
//    '<S2>/Gain4'

#define rtCP_pooled5                   (1.234567901234568E-7)


