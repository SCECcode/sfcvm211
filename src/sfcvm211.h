#ifndef SFCVM211_H
#define SFCVM211_H

/**
 * @file sfcvm211.h
 * @brief Main header file for SFCVM211 library.
 * @author - SCEC 
 * @version 1.0
 *
 * Delivers San Francisco Community Velocity Model
 *
 */

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stdarg.h>

// Constants
#ifndef M_PI
	/** Defines pi */
	#define M_PI 3.14159265358979323846
#endif

typedef enum { SFCVM211_ZMODE_ELEVATION = 0, 
               SFCVM211_ZMODE_DEPTH } zmode_t;

typedef enum { SQUASH_MIN_ELEV = 0 } sfcvm211_model_param_t;


#define NODATA_VALUE -1.0e+20
#define SFCVM211_CONFIG_MAX 1000

// Structures
/** Defines a point (latitude, longitude, and depth) in WGS84 format */
typedef struct sfcvm211_point_t {
	/** Longitude member of the point */
	double longitude;
	/** Latitude member of the point */
	double latitude;
	/** Depth member of the point */
	double depth;
} sfcvm211_point_t;

/** Defines the material properties this model will retrieve. */
typedef struct sfcvm211_properties_t {
	/** P-wave velocity in meters per second */
	double vp;
	/** S-wave velocity in meters per second */
	double vs;
	/** Density in g/m^3 */
	double rho;
        /** NOT USED from basic_property_t */
        double qp;
        /** NOT USED from basic_property_t */
        double qs;
} sfcvm211_properties_t;

/** The SFCVM211 configuration structure. */
typedef struct sfcvm211_configuration_t {
	/** The zone of UTM projection */
	int utm_zone;
	/** The model directory */
	char model_dir[1000];
	/** The model depth */
	int model_depth;
	/** The model gabbro */
	int model_gabbro;
	/** The model squashminelev */
	double model_squashminelev;

        /* raw model datafile */
        char *data_labels[10];
        char *data_files[10];
        double data_gridheights[10];
        int data_cnt;

} sfcvm211_configuration_t;

/** The model structure which points to available portions of the model. */
typedef struct sfcvm211_model_t {
	/** A pointer to the Vp data either in memory or disk. Null if does not exist. */
	void *vp;
	/** Vp status: 0 = not found, 1 = found and not in memory, 2 = found and in memory */
	int vp_status;
} sfcvm211_model_t;

// Constants
/** The version of the model. */
extern const char *sfcvm211_version_string;

/** The config of the model. */
extern char *sfcvm211_config_string;

// Variables
/** Set to 1 when the model is ready for query. */
extern int sfcvm211_is_initialized;

/** Location of the binary data files. */
extern char sfcvm211_data_directory[2000];

/** Configuration parameters. */
extern sfcvm211_configuration_t *sfcvm211_configuration;
/** Holds pointers to the velocity model data OR indicates it can be read from file. */
extern sfcvm211_model_t *sfcvm211_velocity_model;

/** The height of this model's region, in meters. */
extern double sfcvm211_total_height_m;
/** The width of this model's region, in meters. */
extern double sfcvm211_total_width_m;

// UCVM API Required Functions

#ifdef DYNAMIC_LIBRARY

/** Initializes the model */
int model_init(const char *dir, const char *label);
/** Cleans up the model (frees memory, etc.) */
int model_finalize();
/** Returns version information */
int model_version(char *ver, int len);
/** Returns config information */
int model_config(char **config, int *sz);
/** Queries the model */
int model_query(sfcvm211_point_t *points, sfcvm211_properties_t *data, int numpts);
/** Setparam */
int model_setparam(int, int, int);

#endif

// SFCVM211 Related Functions

/** Initializes the model */
int sfcvm211_init(const char *dir, const char *label);
/** Cleans up the model (frees memory, etc.) */
int sfcvm211_finalize();
/** Returns version information */
int sfcvm211_version(char *ver, int len);
/** Queries the model */
int sfcvm211_query(sfcvm211_point_t *points, sfcvm211_properties_t *data, int numpts);
/** Setparam*/
int sfcvm211_setparam(int, int, ...);

// Non-UCVM Helper Functions
/** Reads the configuration file. */
int sfcvm211_read_configuration(char *file, sfcvm211_configuration_t *config);
sfcvm211_configuration_t *sfcvm211_init_configuration();
void sfcvm211_setdebug();
void sfcvm211_print_error(char *err);
int sfcvm211_setzmode(char* z);
int sfcvm211_getsurface(double entry_longitude, double entry_latitude, double *surface, double *top);

#endif
