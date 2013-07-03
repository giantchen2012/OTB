/*=========================================================================

  Program:   Monteverdi2
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See Copyright.txt for details.

  Monteverdi2 is distributed under the CeCILL licence version 2. See
  Licence_CeCILL_V2-en.txt or
  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt for more details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef __mvdImageModelRenderer_h
#define __mvdImageModelRenderer_h

//
// Configuration include.
//// Included at first position before any other ones.
#include "ConfigureMonteverdi2.h"

//
// Qt includes (sorted by alphabetic order)
//// Must be included before system/custom includes.
#include <QtCore>

//
// System includes (sorted by alphabetic order)

//
// ITK includes (sorted by alphabetic order)

//
// OTB includes (sorted by alphabetic order)

//
// Monteverdi includes (sorted by alphabetic order)
#include "Core/mvdTypes.h"
#include "Gui/mvdAbstractModelRenderer.h"

#define USE_BYTE_POINTER_bis 1

//
// External classes pre-declaration.
namespace
{
}

namespace mvd
{
//
// Internal classes pre-declaration.
class Monteverdi2_EXPORT AbstractImageModel;

/** \class ImageModelRenderer
 *
 */
class ImageModelRenderer :
    public AbstractModelRenderer
{
  Q_OBJECT;

//
// Public types.
public:
#if USE_BYTE_POINTER_bis
  typedef QSharedPointer< unsigned char > BytePointer;
#endif

//
// Public methods.
public:
  /** Constructor */
  ImageModelRenderer( QObject* parent = NULL );

  /** Destructor */
  virtual ~ImageModelRenderer();

  /** */
  virtual void paintGL( const RenderingContext& context );

// public slots
public slots:
  void onMovingEvent()
  {
    m_IsMoving = true;
  }

  void onReleasedMouse()
  {
    m_IsMoving = false;
  }

  void OnViewportRegionRepresentationChanged(const PointType& ul, const PointType& lr);

//
// SIGNALS.
signals:
  void ViewportOriginChanged(const IndexType origin);
//
// Protected methods.
protected:

//
// Protected attributes.
protected:

//
// Private methods.
private:

//
// Private attributes.
private:
#if USE_BYTE_POINTER_bis
  BytePointer m_Buffer;
#else
  unsigned char * m_Buffer;
#endif

  bool m_IsMoving;

  double m_PreviousOriginX;
  double m_PreviousOriginY;
  double m_MovingOriginX;
  double m_MovingOriginY;

  // 
  // used for quicklook renderer
  PointType m_SquarePointUL;
  PointType m_SquarePointLR;

  unsigned int m_Texture;

//
// SLOTS.
private slots:
};

} // end namespace 'mvd'

#endif // __mvdImageModelRenderer_h
