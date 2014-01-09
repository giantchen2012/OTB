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
#include "mvdDatabaseBrowserWidget.h"
#include "ui_mvdDatabaseBrowserWidget.h"


/*****************************************************************************/
/* INCLUDE SECTION                                                           */

//
// Qt includes (sorted by alphabetic order)
//// Must be included before system/custom includes.

//
// System includes (sorted by alphabetic order)
#include <cassert>

//
// ITK includes (sorted by alphabetic order)

//
// OTB includes (sorted by alphabetic order)

//
// Monteverdi includes (sorted by alphabetic order)
#include "Gui/mvdDatabaseTreeWidget.h"
#include "Gui/mvdTreeWidgetItem.h"

#define ENABLE_DISPLAY_ID 1

namespace mvd
{

/*
  TRANSLATOR mvd::DatabaseBrowserWidget

  Necessary for lupdate to be aware of C++ namespaces.

  Context comment for translator.
*/


/*****************************************************************************/
/* CONSTANTS                                                                 */


/*****************************************************************************/
/* STATIC IMPLEMENTATION SECTION                                             */


/*****************************************************************************/
/* CLASS IMPLEMENTATION SECTION                                              */

/*******************************************************************************/
DatabaseBrowserWidget
::DatabaseBrowserWidget( QWidget* parent, Qt::WindowFlags flags  ):
  QWidget( parent, flags ),
  m_UI( new mvd::Ui::DatabaseBrowserWidget() ),
  m_DatasetRootItem( NULL ),
  m_DatasetList(),
  m_StartDragPosition(),
  m_SearchText()
{
  m_UI->setupUi( this );

  SetupUI();

  /*
  // Devember 12th, 2013 - Trainee example. 
  QPushButton* button=new QPushButton ("Click me", this);
  layout()->addWidget(button);
  */
}

/*******************************************************************************/
DatabaseBrowserWidget
::~DatabaseBrowserWidget()
{
  delete m_UI;
  m_UI = NULL;
}

/*****************************************************************************/
const QTreeWidgetItem*
DatabaseBrowserWidget
::GetRootItem() const
{
  return m_UI->databaseTreeWidget->invisibleRootItem();
}

/*****************************************************************************/
QTreeWidgetItem*
DatabaseBrowserWidget
::GetRootItem()
{
  return m_UI->databaseTreeWidget->invisibleRootItem();
}

/*******************************************************************************/
QTreeWidgetItem*
DatabaseBrowserWidget
::InsertNodeItem( QTreeWidgetItem* parent,
                  const QString& text,
                  const QVariant& id,
                  const QStringList& columns )
{
  return
    InsertItem(
      parent,
      TreeWidgetItem::ITEM_TYPE_NODE,
      text,
      id,
      columns
    );
}

/*******************************************************************************/
QTreeWidgetItem*
DatabaseBrowserWidget
::InsertLeafItem( QTreeWidgetItem* parent,
                  const QString& text,
                  const QVariant& id,
                  const QStringList& columns )
{
  return
    InsertItem(
      parent,
      TreeWidgetItem::ITEM_TYPE_LEAF,
      text,
      id,
      columns
    );
}

/*******************************************************************************/
QTreeWidgetItem*
DatabaseBrowserWidget
::InsertItem( QTreeWidgetItem* parent,
              TreeWidgetItem::ItemType type,
              const QString& text,
              const QVariant& id,
              const QStringList& columns )
{
  TreeWidgetItem* item =
    new TreeWidgetItem(
      parent,
      text,
      id,
      columns,
      type
    );

  return item;
}

/*******************************************************************************/
void
DatabaseBrowserWidget
::SetDatasetList( const StringPairListType& list )
{
  // qDebug() << this << "::SetDatasetList(" << list << ")";

  // remember dataset list
  m_DatasetList = list;

  // Fill Tree
  FillTree();
}

/*******************************************************************************/
void
DatabaseBrowserWidget
::FillTree()
{
  // get the currentItem Id if any selected.
  // since all the TreeWidgetItem are deleted next, need to remember
  // it in order to set it back
  QString currentItemHash;

  TreeWidgetItem* selectedItem = 
    dynamic_cast< TreeWidgetItem* >(
      GetDatabaseTreeWidget()->currentItem()
    );

  if (selectedItem)
    {
    currentItemHash = selectedItem->GetHash();
    }

  // TODO: Get initial algorithm back (synchronizes two ordered
  // sequences using QTreeWidget::findItems<>().
  //
  // Because:
  // 1. removing items can provoque selection changes;
  // 2. it's needed to re-emit signal to keep current selection
  // active.
  //
  // Initial algorithm took care of current-selection and was
  // optimized to not delete useful items which must be inserted
  // again.

  // Remove all previously stored dataset child items.
  while( m_DatasetRootItem->childCount()>0 )
    {
    // Remove dataset child item and reference it.
    QTreeWidgetItem* child = m_DatasetRootItem->takeChild( 0 );

    // Delete it from memory.
    delete child;
    child = NULL;
    }

  // Append full dataset list...
  for( StringPairListType::const_iterator it( m_DatasetList.begin() );
       it!=m_DatasetList.end();
       ++it )
    {
    // current alias
    const StringPairListType::value_type::first_type& alias = it->first;
    const StringPairListType::value_type::second_type& hash = it->second;

    TreeWidgetItem* item =
      new TreeWidgetItem(
        m_DatasetRootItem,
        alias,
        QVariant(),
        QStringList( hash )
      );

    // Item is visible is search-text is empty or if alias contains
    // search-text.
    item->setHidden(
      !m_SearchText.isEmpty() &&
      !item->text( 0 ).contains( m_SearchText, Qt::CaseInsensitive )
    );

    // was it the selected item ?
    if( currentItemHash == hash )
      {
      // ...add this child item as currentItem
      GetDatabaseTreeWidget()->setCurrentItem( item );
      }
    }
}

/*****************************************************************************/
void
DatabaseBrowserWidget
::SetupUI()
{
  setAcceptDrops( true );

  //
  // Header columns.
  m_UI->databaseTreeWidget->headerItem()->setText( 1, "Id" );
  m_UI->databaseTreeWidget->headerItem()->setText( 2, "Info" );

#if (!defined( _DEBUG ) && 1) || 0
  m_UI->databaseTreeWidget->setColumnHidden( 1, true );
  m_UI->databaseTreeWidget->setColumnHidden( 2, true );
#endif

  //
  // Dataset root item.
#if 0
  m_DatasetRootItem = new QTreeWidgetItem( "Datasets", m_UI->databaseTreeWidget );

  m_DatasetRootItem->setChildIndicatorPolicy(
    QTreeWidgetItem::DontShowIndicatorWhenChildless
  );

  m_DatasetRootItem->setExpanded( true );
#endif

  // set placeholder text
#if (QT_VERSION >= 0x407000)
  m_UI->m_SearchLine->setPlaceholderText( tr( "Search Dataset..." ) );
#endif
}

/*******************************************************************************/
DatabaseTreeWidget*
DatabaseBrowserWidget
::GetDatabaseTreeWidget()
{
  return m_UI->databaseTreeWidget;
}

/*****************************************************************************/
void
DatabaseBrowserWidget
::SetCurrentDataset( const QString& hash )
{
  // qDebug() << this << "::SetCurrentDataset(" << id << ")";

  assert( m_UI!=NULL );
  assert( m_UI->databaseTreeWidget!=NULL );

  QList< QTreeWidgetItem* > items(
    m_UI->databaseTreeWidget->findItems(
      hash,
      Qt::MatchExactly | Qt::MatchRecursive,
      1
    )
  );

  assert( items.isEmpty() || items.size() == 1 );

  /*
  qDebug()
    << ( items.isEmpty() ? "NONE" : items.first()->text( 0 ) )
    << m_UI->databaseTreeWidget->selectionModel()->selectedIndexes().size();
  */

#if 0

   m_UI->databaseTreeWidget->setCurrentItem(
    items.isEmpty() ? NULL : items.first(),
    0,
    QItemSelectionModel::Clear |
    QItemSelectionModel::Current
  );
#else
  if( items.isEmpty() )
    return;

  m_UI->databaseTreeWidget->setCurrentItem( items.first() );
#endif
}

/*******************************************************************************/
/* SLOTS                                                                       */
/*******************************************************************************/
void
DatabaseBrowserWidget
::on_databaseTreeWidget_currentItemChanged( QTreeWidgetItem* current,
					    QTreeWidgetItem* previous )
{
  //
  // Current

  // TODO: Should be DatabaseModel::DatasetId but widgets should not depend on models!!!
  QString currentHash;

  TreeWidgetItem* currentItem = dynamic_cast< TreeWidgetItem* >( current );

  if( currentItem!=NULL && currentItem->parent()!=NULL )
    // if current is root and not NULL get the Id of the corresponding
    // Dataset.
    currentHash = currentItem->GetHash();

  //
  // Previous

  // TODO: Should be DatabaseModel::DatasetId but widgets should not depend on models!!!
  QString previousHash;

  TreeWidgetItem* previousItem = dynamic_cast< TreeWidgetItem* >( previous );

  if( previousItem!=NULL )
    previousHash = previousItem->GetHash();

  //
  // Emit event.
  emit CurrentDatasetChanged( currentHash, previousHash );
}

/*******************************************************************************/
void
DatabaseBrowserWidget
::on_m_SearchLine_textChanged( const QString& search )
{
  // 
  // get the search text
  m_SearchText = search;

#if 0
  // fill the tree with the application
  FillTree();  
#else
  if( m_DatasetRootItem==NULL )
    return;

  for( int i=0; i<m_DatasetRootItem->childCount();  ++i )
    {
    QTreeWidgetItem* item = m_DatasetRootItem->child( i );
    assert( item!=NULL );

    // Item is visible if search is empty or if alias contains
    // search-text.
    item->setHidden(
      !search.isEmpty() &&
      !item->text( 0 ).contains( search, Qt::CaseInsensitive )
    );
    }
#endif
}

} // end namespace 'mvd'