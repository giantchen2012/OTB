/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#define MAIN

#include "otbImage.h"
#include "otbLogPolarResampleImageFilter.h"
#include "itkLinearInterpolateImageFunction.h"

int otbLogPolarResampleImageFilterNew(int argc, char* argv[])
{

  typedef double                                          PixelType;
  const   unsigned int        	                          Dimension = 2;

  typedef otb::Image< PixelType, Dimension >        InputImageType;
  typedef otb::Image< PixelType, Dimension >        OutputImageType;
   
  typedef itk::LinearInterpolateImageFunction< InputImageType, double >	InterpolatorType;
  typedef otb::LogPolarResampleImageFilter<InputImageType,InterpolatorType> LogPolarResampleImageType;
  try 
    { 
     LogPolarResampleImageType::Pointer LogPolarImage = LogPolarResampleImageType::New();
    } 
  catch( itk::ExceptionObject & err ) 
    { 
    std::cerr << "itk::Exception detected: "  << err.GetDescription();
    return EXIT_FAILURE;
    } 
  catch( ... ) 
    { 
    std::cout << "unknown exception detected !" << std::endl; 
    return EXIT_FAILURE;
    } 
  
  return EXIT_SUCCESS;
}
