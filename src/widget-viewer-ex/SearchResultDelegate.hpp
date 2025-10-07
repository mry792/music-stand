#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QStyledItemDelegate>

class QModelIndex;
class QPainter;
class QStyleOptionViewItem;


namespace widget_viewer {
class SearchResultDelegate : public QStyledItemDelegate {
    Q_OBJECT

  public:
    explicit SearchResultDelegate (QObject* parent = nullptr);

    void paint(
        QPainter* painter,
        QStyleOptionViewItem const& option,
        QModelIndex const& index
    ) const override;
};
}  // namespace widget_viewer
