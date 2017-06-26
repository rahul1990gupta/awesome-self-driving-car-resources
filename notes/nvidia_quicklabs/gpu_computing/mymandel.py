from contextlib import contextmanager
import time
import numpy as np
from pylab import imshow, show
from numba import *

@autojit
def mandel(x, y, max_iters):
  """
    Given the real and imaginary parts of a complex number,
    determine if it is a candidate for membership in the Mandelbrot
    set given a fixed number of iterations.
  """
  c = complex(x, y)
  z = 0.0j
  for i in xrange(max_iters):
    z = z*z + c
    if (z.real*z.real + z.imag*z.imag) >= 4:
      return i

  return max_iters

# The compiled CPU version of the fractal code
@autojit
def create_fractal_cpu(min_x, max_x, min_y, max_y, image, iters):
  height = image.shape[0]
  width = image.shape[1]

  pixel_size_x = (max_x - min_x) / width
  pixel_size_y = (max_y - min_y) / height
    
  for x in xrange(width):
    real = min_x + x * pixel_size_x
    for y in xrange(height):
      imag = min_y + y * pixel_size_y
      color = mandel(real, imag, iters)
      image[y, x] = color

# create a GPU accelerated version of the madel function 
#so it can be called from other device functions like mandel_kernel
mandel_gpu = cuda.jit(restype=uint32, argtypes=[f8, f8, uint32], device=True)(mandel)

# The compiled GPU version of the fractal code
@cuda.jit(argtypes=[f8, f8, f8, f8, uint8[:,:], uint32])
def create_fractal_gpu(min_x, max_x, min_y, max_y, image, iters):
  height = image.shape[0]
  width = image.shape[1]
    
  pixel_size_x = (max_x - min_x) / width
  pixel_size_y = (max_y - min_y) / height

  startX, startY = cuda.grid(2) # startX = cuda.threadIdx.x + cuda.blockDim.x * cuda.BlockIdx.x
                                # startX = cuda.threadIdx.x + cuda.blockDim.x * cuda.BlockIdx.x
  gridX = cuda.gridDim.x * cuda.blockDim.x; # Number of threads, or size of image in X direction
  gridY = cuda.gridDim.y * cuda.blockDim.y; # Number of threads, or size of image in Y direction

  for x in xrange(startX, width, gridX):
    real = min_x + x * pixel_size_x
    for y in xrange(startY, height, gridY):
      imag = min_y + y * pixel_size_y 
      image[y, x] = mandel_gpu(real, imag, iters)

# Used for timing sections of code
@contextmanager
def mytimer(name):
    startTime = time.time()
    yield
    elapsedTime = time.time() - startTime
    print('{} in {} ms'.format(name, int(elapsedTime * 1000)))
