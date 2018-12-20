#include "controller_tdf.hh"


controller::controller( sc_core::sc_module_name ):
  in("in"),
  out("out"),
  Ts(0.02)
{
#ifdef TRACING
  log_error = fopen( "logs/error.log", "w" );
  log_reference = fopen( "logs/reference.log", "w" );
#endif
#ifdef REAL
  s = 0;
#endif
}

controller::~controller()
{
#ifdef TRACING
  if( log_error != NULL ) fclose(log_error);
  if( log_reference != NULL ) fclose(log_reference);
#endif
}

void controller::set_attributes()
{

  set_timestep( sca_core::sca_time( Ts, sc_core::SC_SEC ) );

  in.set_rate(1);
  out.set_rate(1);
  out.set_delay(1);

}

void controller::ac_processing()
{
}

void controller::processing()
{
  ref = reference[s % 500];
  ++s;
  prev = ref;

  double error = in.read() - prev;

#ifdef TRACING
  fprintf( log_error, "%f %f\n", sc_time_stamp().to_seconds(), error );
  fprintf( log_reference, "%f %f\n", sc_time_stamp().to_seconds(), ref );
#endif
  out.write( ref );
;
}

double reference[500] = {
0.000000,
0.001885,
0.010228,
0.014163,
0.016651,
0.026319,
0.050984,
0.065362,
0.067741,
0.052274,
0.029000,
-0.002408,
-0.039668,
-0.067342,
-0.091830,
-0.115336,
-0.148361,
-0.176663,
-0.216220,
-0.254581,
-0.288600,
-0.325664,
-0.361024,
-0.392756,
-0.432354,
-0.473020,
-0.508295,
-0.534133,
-0.547601,
-0.567142,
-0.581824,
-0.597219,
-0.609813,
-0.615168,
-0.604365,
-0.594858,
-0.583917,
-0.560728,
-0.550315,
-0.548983,
-0.540412,
-0.538489,
-0.522291,
-0.494864,
-0.475924,
-0.463872,
-0.448585,
-0.435202,
-0.430962,
-0.433078,
-0.433389,
-0.421694,
-0.400819,
-0.389752,
-0.382146,
-0.380595,
-0.384126,
-0.378739,
-0.371493,
-0.364469,
-0.342751,
-0.315277,
-0.294272,
-0.277262,
-0.246253,
-0.201545,
-0.164181,
-0.141014,
-0.098459,
-0.058149,
-0.019121,
0.012044,
0.054418,
0.096486,
0.135271,
0.166527,
0.198087,
0.232196,
0.273047,
0.287197,
0.306124,
0.322044,
0.351653,
0.377702,
0.415937,
0.453966,
0.480630,
0.491910,
0.494286,
0.507213,
0.518969,
0.530192,
0.551565,
0.564163,
0.567680,
0.562122,
0.559830,
0.556156,
0.541993,
0.511964,
0.491720,
0.475625,
0.467880,
0.474913,
0.482016,
0.484155,
0.481119,
0.473200,
0.483212,
0.493427,
0.503198,
0.515766,
0.523986,
0.530713,
0.536959,
0.537499,
0.538377,
0.531265,
0.523490,
0.522977,
0.526079,
0.529027,
0.517267,
0.491111,
0.454164,
0.409039,
0.348922,
0.291470,
0.238786,
0.182533,
0.132340,
0.084793,
0.028690,
-0.030142,
-0.107677,
-0.196189,
-0.282459,
-0.362092,
-0.411019,
-0.450039,
-0.482475,
-0.535964,
-0.583369,
-0.635430,
-0.685971,
-0.737863,
-0.784563,
-0.819198,
-0.858207,
-0.899053,
-0.944940,
-0.987787,
-1.018478,
-1.043030,
-1.049477,
-1.063064,
-1.073515,
-1.067921,
-1.063338,
-1.044549,
-1.028673,
-1.016534,
-1.011588,
-1.000926,
-0.984602,
-0.979566,
-0.965023,
-0.943999,
-0.924721,
-0.906633,
-0.883386,
-0.856917,
-0.832894,
-0.819043,
-0.806210,
-0.804370,
-0.790019,
-0.745354,
-0.696239,
-0.654173,
-0.608250,
-0.564341,
-0.507919,
-0.442836,
-0.387528,
-0.342955,
-0.313842,
-0.282326,
-0.266465,
-0.258505,
-0.253146,
-0.250897,
-0.239188,
-0.232563,
-0.237836,
-0.244783,
-0.241567,
-0.237361,
-0.230568,
-0.239110,
-0.251330,
-0.247905,
-0.245871,
-0.237905,
-0.222642,
-0.207268,
-0.197906,
-0.203121,
-0.208564,
-0.211039,
-0.225910,
-0.241043,
-0.243977,
-0.242696,
-0.249724,
-0.239832,
-0.215614,
-0.189791,
-0.168060,
-0.143189,
-0.120283,
-0.097925,
-0.075969,
-0.051900,
-0.031228,
0.005789,
0.039091,
0.086132,
0.147431,
0.207293,
0.266017,
0.319347,
0.372204,
0.420309,
0.471675,
0.515700,
0.548622,
0.579357,
0.616079,
0.644898,
0.653673,
0.639149,
0.624002,
0.598715,
0.569466,
0.541107,
0.512451,
0.481327,
0.448824,
0.417130,
0.391441,
0.374469,
0.366690,
0.357755,
0.340153,
0.312507,
0.279711,
0.256761,
0.241790,
0.222303,
0.216820,
0.201448,
0.183519,
0.176534,
0.163946,
0.141820,
0.117924,
0.084672,
0.042372,
0.013034,
-0.012512,
-0.046403,
-0.083261,
-0.107613,
-0.137526,
-0.164264,
-0.182354,
-0.199664,
-0.215333,
-0.228144,
-0.230677,
-0.235107,
-0.242115,
-0.248807,
-0.271553,
-0.298178,
-0.340150,
-0.373944,
-0.401357,
-0.425470,
-0.449273,
-0.464099,
-0.480290,
-0.495578,
-0.511941,
-0.533389,
-0.555642,
-0.568477,
-0.581263,
-0.585806,
-0.588749,
-0.596663,
-0.609642,
-0.611841,
-0.606494,
-0.597918,
-0.607160,
-0.619591,
-0.630263,
-0.635657,
-0.655326,
-0.668994,
-0.676017,
-0.678699,
-0.675923,
-0.676900,
-0.674090,
-0.676579,
-0.681472,
-0.676514,
-0.682013,
-0.695818,
-0.701637,
-0.710777,
-0.714490,
-0.722640,
-0.743874,
-0.752557,
-0.748279,
-0.737981,
-0.719435,
-0.703992,
-0.703670,
-0.701282,
-0.714901,
-0.736686,
-0.743001,
-0.733836,
-0.715468,
-0.716207,
-0.727592,
-0.742665,
-0.754037,
-0.758229,
-0.748950,
-0.732665,
-0.719366,
-0.696269,
-0.684542,
-0.670553,
-0.643684,
-0.626785,
-0.611170,
-0.599101,
-0.585751,
-0.574603,
-0.574287,
-0.593340,
-0.619887,
-0.658132,
-0.696994,
-0.721854,
-0.760867,
-0.795372,
-0.815370,
-0.840653,
-0.859781,
-0.867577,
-0.866603,
-0.882224,
-0.891611,
-0.891890,
-0.890977,
-0.888391,
-0.887551,
-0.902260,
-0.932086,
-0.964624,
-0.988488,
-1.003994,
-1.014187,
-1.038471,
-1.064874,
-1.077665,
-1.075907,
-1.070567,
-1.061290,
-1.071827,
-1.086945,
-1.076911,
-1.058626,
-1.036095,
-1.014742,
-0.997305,
-0.991956,
-0.993925,
-1.001276,
-0.992512,
-0.956918,
-0.909967,
-0.858653,
-0.801889,
-0.742605,
-0.684432,
-0.624602,
-0.572370,
-0.533617,
-0.497318,
-0.470219,
-0.446746,
-0.431323,
-0.406630,
-0.371036,
-0.330692,
-0.287977,
-0.250029,
-0.213537,
-0.169186,
-0.118226,
-0.066275,
-0.020302,
0.031052,
0.088524,
0.137414,
0.184098,
0.217438,
0.247457,
0.275299,
0.299653,
0.343402,
0.391090,
0.440042,
0.484897,
0.525244,
0.556824,
0.594786,
0.637664,
0.683494,
0.704919,
0.729719,
0.753000,
0.773426,
0.790091,
0.805336,
0.811154,
0.801750,
0.782974,
0.756288,
0.731729,
0.712232,
0.687284,
0.669248,
0.645935,
0.620011,
0.597190,
0.565238,
0.524800,
0.483962,
0.440927,
0.390763,
0.335075,
0.290856,
0.243879,
0.195956,
0.144412,
0.093487,
0.046692,
0.001171,
-0.042984,
-0.096169,
-0.155195,
-0.201569,
-0.239809,
-0.263891,
-0.285282,
-0.318025,
-0.331435,
-0.337231,
-0.336284,
-0.327074,
-0.326781,
-0.322373,
-0.309762,
-0.295675,
-0.286640,
-0.279772,
-0.258823,
-0.230930,
-0.200602,
-0.166731,
-0.128477,
-0.093718,
-0.070928,
-0.048081,
-0.039020,
-0.032385,
-0.029213,
-0.021140,
-0.017743,
-0.011537
};

