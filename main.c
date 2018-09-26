/****************************************************************************
 *
 * Demo for ARTIK 055 board.
 *
 * Author: zhanzr@foxmail.com
 * Date:	11:50 PM 9/26/2018
 * Description:
 *
 ****************************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <apps/shell/tash.h>

#include "cJSON/cJSON.h"

typedef struct str_poi_record {
  const char *precision;
  double lat;
  double lon;
  const char *address;
  const char *city;
  const char *state;
  const char *zip;
  const char *country;
} poi_record;

/* Our "days of the week" array: */
const char *str_weekdays[7] = {"Sunday",   "Monday", "Tuesday", "Wednesday",
                               "Thursday", "Friday", "Saturday"};

/* Our matrix: */
const int numbers[3][3] = {{0, -1, 0}, {1, 0, 0}, {0, 0, 1}};

/* Our "gallery" item: */
const int ids[4] = {116, 943, 234, 38793};
/* Our array of "records": */
const poi_record fields[2] = {
    {"zip", 37.7668, -1.223959e+2, "", "SAN FRANCISCO", "CA", "94107", "US"},
    {"zip", 37.371991, -1.22026e+2, "", "SUNNYVALE", "CA", "94085", "US"}};

/* Create a bunch of objects as demonstration. */
static int print_preallocated(cJSON *root) {
  /* declarations */
  char *out = NULL;
  char *buf = NULL;
  char *buf_fail = NULL;
  size_t len = 0;
  size_t len_fail = 0;

  /* formatted print */
  out = cJSON_Print(root);

  /* create buffer to succeed */
  /* the extra 5 bytes are because of inaccuracies when reserving memory */
  len = strlen(out) + 5;
  buf = (char *)malloc(len);
  if (buf == NULL) {
    printf("Failed to allocate memory.\n");
    exit(1);
  }

  /* create buffer to fail */
  len_fail = strlen(out);
  buf_fail = (char *)malloc(len_fail);
  if (buf_fail == NULL) {
    printf("Failed to allocate memory.\n");
    exit(1);
  }

  /* Print to buffer */
  if (!cJSON_PrintPreallocated(root, buf, (int)len, 1)) {
    printf("cJSON_PrintPreallocated failed!\n");
    if (strcmp(out, buf) != 0) {
      printf("cJSON_PrintPreallocated not the same as cJSON_Print!\n");
      printf("cJSON_Print result:\n%s\n", out);
      printf("cJSON_PrintPreallocated result:\n%s\n", buf);
    }
    free(out);
    free(buf_fail);
    free(buf);
    return -1;
  }

  /* success */
  printf("%s\n", buf);

  /* force it to fail */
  if (cJSON_PrintPreallocated(root, buf_fail, (int)len_fail, 1)) {
    printf("cJSON_PrintPreallocated failed to show error with insufficient "
           "memory!\n");
    printf("cJSON_Print result:\n%s\n", out);
    printf("cJSON_PrintPreallocated result:\n%s\n", buf_fail);
    free(out);
    free(buf_fail);
    free(buf);
    return -1;
  }

  free(out);
  free(buf_fail);
  free(buf);
  return 0;
}

/* Create a bunch of objects as demonstration. */
static void create_objects(void) {
  /* declare a few. */
  cJSON *root = NULL;
  cJSON *fmt = NULL;
  cJSON *img = NULL;
  cJSON *thm = NULL;
  cJSON *fld = NULL;
  int i = 0;

  volatile double zero = 0.0;

  /* Here we construct some JSON standards, from the JSON site. */

  /* Our "Video" datatype: */
  root = cJSON_CreateObject();
  cJSON_AddItemToObject(root, "name",
                        cJSON_CreateString("Jack (\"Bee\") Nimble"));
  cJSON_AddItemToObject(root, "format", fmt = cJSON_CreateObject());
  cJSON_AddStringToObject(fmt, "type", "rect");
  cJSON_AddNumberToObject(fmt, "width", 1920);
  cJSON_AddNumberToObject(fmt, "height", 1080);
  cJSON_AddFalseToObject(fmt, "interlace");
  cJSON_AddNumberToObject(fmt, "frame rate", 24);

  /* Print to text */
  if (print_preallocated(root) != 0) {
    cJSON_Delete(root);
    exit(EXIT_FAILURE);
  }
  cJSON_Delete(root);

  /* Our "days of the week" array: */
  root = cJSON_CreateStringArray(str_weekdays, 7);

  if (print_preallocated(root) != 0) {
    cJSON_Delete(root);
    exit(EXIT_FAILURE);
  }
  cJSON_Delete(root);

  /* Our matrix: */
  root = cJSON_CreateArray();
  for (i = 0; i < 3; i++) {
    cJSON_AddItemToArray(root, cJSON_CreateIntArray(numbers[i], 3));
  }

  /* cJSON_ReplaceItemInArray(root, 1, cJSON_CreateString("Replacement")); */

  if (print_preallocated(root) != 0) {
    cJSON_Delete(root);
    exit(EXIT_FAILURE);
  }
  cJSON_Delete(root);

  /* Our "gallery" item: */
  root = cJSON_CreateObject();
  cJSON_AddItemToObject(root, "Image", img = cJSON_CreateObject());
  cJSON_AddNumberToObject(img, "Width", 800);
  cJSON_AddNumberToObject(img, "Height", 600);
  cJSON_AddStringToObject(img, "Title", "View from 15th Floor");
  cJSON_AddItemToObject(img, "Thumbnail", thm = cJSON_CreateObject());
  cJSON_AddStringToObject(thm, "Url", "http:/*www.example.com/image/481989943");
  cJSON_AddNumberToObject(thm, "Height", 125);
  cJSON_AddStringToObject(thm, "Width", "100");
  cJSON_AddItemToObject(img, "IDs", cJSON_CreateIntArray(ids, 4));

  if (print_preallocated(root) != 0) {
    cJSON_Delete(root);
    exit(EXIT_FAILURE);
  }
  cJSON_Delete(root);

  /* Our array of "records": */
  root = cJSON_CreateArray();
  for (i = 0; i < 2; i++) {
    cJSON_AddItemToArray(root, fld = cJSON_CreateObject());
    cJSON_AddStringToObject(fld, "precision", fields[i].precision);
    cJSON_AddNumberToObject(fld, "Latitude", fields[i].lat);
    cJSON_AddNumberToObject(fld, "Longitude", fields[i].lon);
    cJSON_AddStringToObject(fld, "Address", fields[i].address);
    cJSON_AddStringToObject(fld, "City", fields[i].city);
    cJSON_AddStringToObject(fld, "State", fields[i].state);
    cJSON_AddStringToObject(fld, "Zip", fields[i].zip);
    cJSON_AddStringToObject(fld, "Country", fields[i].country);
  }

  /* cJSON_ReplaceItemInObject(cJSON_GetArrayItem(root, 1), "City",
   * cJSON_CreateIntArray(ids, 4)); */

  if (print_preallocated(root) != 0) {
    cJSON_Delete(root);
    exit(EXIT_FAILURE);
  }
  cJSON_Delete(root);

  root = cJSON_CreateObject();
  cJSON_AddNumberToObject(root, "number", 1.0 / zero);

  if (print_preallocated(root) != 0) {
    cJSON_Delete(root);
    exit(EXIT_FAILURE);
  }
  cJSON_Delete(root);
}

// create a monitor with a list of supported resolutions
// NOTE: Returns a heap allocated string, you are required to free it after use.
char *create_monitor(void) {
  const unsigned int resolution_numbers[3][2] = {
      {1280, 720}, {1920, 1080}, {3840, 2160}};
  char *string = NULL;
  cJSON *name = NULL;
  cJSON *resolutions = NULL;
  cJSON *resolution = NULL;
  cJSON *width = NULL;
  cJSON *height = NULL;
  size_t index = 0;

  cJSON *monitor = cJSON_CreateObject();
  if (monitor == NULL) {
    goto end;
  }

  name = cJSON_CreateString("Display AOC");
  if (name == NULL) {
    goto end;
  }
  /* after creation was successful, immediately add it to the monitor,
   * thereby transferring ownership of the pointer to it */
  cJSON_AddItemToObject(monitor, "name", name);

  resolutions = cJSON_CreateArray();
  if (resolutions == NULL) {
    goto end;
  }
  cJSON_AddItemToObject(monitor, "resolutions", resolutions);

  for (index = 0; index < (sizeof(resolution_numbers) / (2 * sizeof(int)));
       ++index) {
    resolution = cJSON_CreateObject();
    if (resolution == NULL) {
      goto end;
    }
    cJSON_AddItemToArray(resolutions, resolution);

    width = cJSON_CreateNumber(resolution_numbers[index][0]);
    if (width == NULL) {
      goto end;
    }
    cJSON_AddItemToObject(resolution, "width", width);

    height = cJSON_CreateNumber(resolution_numbers[index][1]);
    if (height == NULL) {
      goto end;
    }
    cJSON_AddItemToObject(resolution, "height", height);
  }

  string = cJSON_Print(monitor);
  if (string == NULL) {
    fprintf(stderr, "Failed to print monitor.\n");
  }

end:

  print_preallocated(monitor);

  cJSON_Delete(monitor);
  return string;
}

// NOTE: Returns a heap allocated string, you are required to free it after use.
char *create_monitor_with_helpers(void) {
  const unsigned int resolution_numbers[3][2] = {
      {1280, 720}, {1920, 1080}, {3840, 2160}};
  char *string = NULL;
  cJSON *resolutions = NULL;
  size_t index = 0;

  cJSON *monitor = cJSON_CreateObject();

  cJSON_AddStringToObject(monitor, "name", "Display LGD");

  resolutions = cJSON_AddArrayToObject(monitor, "resolutions");
  if (resolutions == NULL) {
    goto end;
  }

  for (index = 0; index < (sizeof(resolution_numbers) / (2 * sizeof(int)));
       ++index) {
    cJSON *resolution = cJSON_CreateObject();

    cJSON_AddNumberToObject(resolution, "width", resolution_numbers[index][0]);

    cJSON_AddNumberToObject(resolution, "height", resolution_numbers[index][1]);

    cJSON_AddItemToArray(resolutions, resolution);
  }

  string = cJSON_Print(monitor);
  if (string == NULL) {
    fprintf(stderr, "Failed to print monitor.\n");
  }

end:
  print_preallocated(monitor);

  cJSON_Delete(monitor);
  return string;
}

/* return 1 if the monitor supports full hd, 0 otherwise */
int supports_resolution(const char *const monitor, int wid, int hgt) {
  const cJSON *resolution = NULL;
  const cJSON *resolutions = NULL;
  const cJSON *name = NULL;
  int status = 0;
  cJSON *monitor_json = cJSON_Parse(monitor);
  if (monitor_json == NULL) {
    const char *error_ptr = cJSON_GetErrorPtr();
    if (error_ptr != NULL) {
      fprintf(stderr, "Error before: %s\n", error_ptr);
    }
    status = 0;
    goto end;
  }

  name = cJSON_GetObjectItemCaseSensitive(monitor_json, "name");
  if (cJSON_IsString(name) && (name->valuestring != NULL)) {
    printf("Checking monitor \"%s\"\n", name->valuestring);
  }

  resolutions = cJSON_GetObjectItemCaseSensitive(monitor_json, "resolutions");
  //    cJSON_ArrayForEach(resolution, resolutions)
  for (resolution = (resolutions != NULL) ? (resolutions)->child : NULL;
       resolution != NULL; resolution = resolution->next) {
    cJSON *width = cJSON_GetObjectItemCaseSensitive(resolution, "width");
    cJSON *height = cJSON_GetObjectItemCaseSensitive(resolution, "height");

    if (!cJSON_IsNumber(width) || !cJSON_IsNumber(height)) {
      status = 0;
      goto end;
    }

    if ((width->valuedouble == wid) && (height->valuedouble == hgt)) {
      status = 1;
      goto end;
    }
  }

end:
  cJSON_Delete(monitor_json);
  return status;
}

void test_cJSON(void) {
  printf("cJSON Version: %s\n", cJSON_Version());

  /* Now some samplecode for building objects concisely: */
  create_objects();

  char *monitor = create_monitor();
  int support_hd_ret = supports_resolution(monitor, 1920, 1080);
  printf("support_hd:%d\n", support_hd_ret);
  free(monitor);

  monitor = create_monitor_with_helpers();
  int support_4k_ret = supports_resolution(monitor, 3840, 2160);
  printf("support_4k:%d\n", support_4k_ret);
  free(monitor);
}

void find_max_calloc(void) {
  int *p;
  uint32_t count = 0;
  while (1) {
    int inc = 2048 * sizeof(char);
    p = (int *)calloc(1, inc);
    if (!p) {
      printf("%u KiB\n", count * 2);
      break;
    } else {
      count++;
    }
  }
}

#ifdef CONFIG_BUILD_KERNEL
int main(int argc, FAR char *argv[])
#else
int demo_main(int argc, FAR char *argv[])
#endif
{
  int ret = 0;

  adctest(1);

  test_cJSON();

  printf("%u %u %u\n", sizeof(int), sizeof(long), sizeof(long long));

  find_max_calloc();

  return ret;
}
