// Copyright (c) 2012-2016, Jeffrey N. Johnson
// All rights reserved.
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "polywog/sph_kernel.h"

struct sph_kernel_t 
{
  char* name;
  void* context;
  void (*compute)(void* context, point_t* x, real_t* H, real_t* W, vector_t* grad_W);
  void (*dtor)(void* context);
};

sph_kernel_t* sph_kernel_new(const char* name,
                             void* context,
                             void (*compute)(void* context, point_t* x, real_t* H, real_t* W, vector_t* grad_W),
                             void (*dtor)(void* context))
{
  sph_kernel_t* kernel = polymec_malloc(sizeof(sph_kernel_t));
  kernel->name = string_dup(name);
  kernel->context = context;
  kernel->compute = compute;
  kernel->dtor = dtor;
  return kernel;
}

void sph_kernel_free(sph_kernel_t* kernel)
{
  if ((kernel->dtor != NULL) && (kernel->context != NULL))
    kernel->dtor(kernel->context);
  string_free(kernel->name);
  polymec_free(kernel);
}

void sph_kernel_compute(sph_kernel_t* kernel, point_t* x, real_t* H, real_t* W, vector_t* grad_W)
{
  kernel->compute(kernel->context, x, H, W, grad_W);
}

