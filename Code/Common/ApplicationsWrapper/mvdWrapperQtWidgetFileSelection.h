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
#ifndef __mvdWrapperQtWidgetFileSelection_h
#define __mvdWrapperQtWidgetFileSelection_h

/*****************************************************************************/
/* INCLUDE SECTION                                                           */

//
// Qt includes (sorted by alphabetic order)
//// Must be included before system/custom includes.
#include <QtGui>

//
// System includes (sorted by alphabetic order)

//
// ITK includes (sorted by alphabetic order)

//
// OTB includes (sorted by alphabetic order)

//
// Monteverdi includes (sorted by alphabetic order)


/*****************************************************************************/
/* PRE-DECLARATION SECTION                                                   */

//
// External classes pre-declaration.
namespace
{
}

namespace mvd
{
class DropLineEdit;

namespace Wrapper
{

/*****************************************************************************/
/* CLASS DEFINITION SECTION                                                  */

/**
 * \class QtWidgetFileSelection
 *
 * \brief WIP.
 */

class QtWidgetFileSelection : public QWidget
{
    /*-[ QOBJECT SECTION ]-----------------------------------------------------*/

  Q_OBJECT

  /*-[ PUBLIC SECTION ]------------------------------------------------------*/

//
// Public methods.
public:
  
   /** \brief Constructor. */
  QtWidgetFileSelection();

  /** \brief destructor. */
  virtual ~QtWidgetFileSelection();

  /** \brief convenient methods */

  bool IsChecked()
  {
    return m_Checkbox->isChecked();
  }

  void SetChecked( bool val )
  {
    return m_Checkbox->setChecked( val );
  }

  std::string GetFilename()
  {
    return static_cast<const char*>( m_Input->text().toAscii() );
  }

  void ClearFilename()
  {
    m_Input->clear();
  }

  /*
  DropLineEdit* GetInput()
  {
    return m_Input;
  }
  */

signals:
  void textChanged(const QString &);

protected slots:
  void SelectFile();

protected:

#if 0
  /** \brief drag and drop events reimplementation */
  void dragEnterEvent( QDragEnterEvent * event );
  void dropEvent( QDropEvent *event );
  void dragMoveEvent(QDragMoveEvent *event);
#endif

private:
  QtWidgetFileSelection(const QtWidgetFileSelection&); //purposely not implemented
  void operator=(const QtWidgetFileSelection&); //purposely not implemented

  virtual void DoCreateWidget();

  virtual void DoUpdateGUI();

  std::string ExtractValidFilename(std::string payload);

  QHBoxLayout* m_HLayout;
  QLineEdit* m_Input;
  QPushButton* m_Button;
  QCheckBox* m_Checkbox;
};

}

}

#endif