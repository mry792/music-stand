#include "SearchResultDelegate.hpp"

#include <QtCore/QModelIndex>
#include <QtCore/QString>
#include <QtCore/Qt>
#include <QtGui/QFont>
#include <QtGui/QFontMetrics>
#include <QtGui/QPainter>
#include <QtPdf/QPdfSearchModel>
#include <QtWidgets/QStyle>
#include <QtWidgets/QStyleOption>


namespace widget_viewer {
// explicit
SearchResultDelegate::SearchResultDelegate (QObject* parent)
      : QStyledItemDelegate{parent} {}

// override
void SearchResultDelegate::paint(
    QPainter* painter,
    QStyleOptionViewItem const& option,
    QModelIndex const& index
) const {
    auto const display_text = index.data().toString();
    auto const bold_begin = display_text.indexOf(u"<b>", 0, Qt::CaseInsensitive) + 3;
    auto const bold_end = display_text.indexOf(u"</b>", bold_begin, Qt::CaseInsensitive);

    if (bold_begin >= 3 and bold_end > bold_begin) {
        int const page_number = index.data(static_cast<int>(QPdfSearchModel::Role::Page)).toInt();
        auto const page_label = tr("Page %1: ").arg(page_number);
        auto const bold_text = display_text.mid(bold_begin, bold_end - bold_begin);

        if (option.state bitand QStyle::State_Selected) {
            painter->fillRect(option.rect, option.palette.highlight());
        }

        QFont const default_font = painter->font();
        QFontMetrics font_metrics = painter->fontMetrics();
        auto page_label_width = font_metrics.horizontalAdvance(page_label);
        int const y_offset = (option.rect.height() - font_metrics.height()) / 2 + font_metrics.ascent();
        painter->drawText(0, option.rect.y() + y_offset, page_label);

        QFont bold_font = default_font;
        bold_font.setBold(true);
        auto bold_width = QFontMetrics{bold_font}.horizontalAdvance(bold_text);
        auto prefix_suffix_width = (option.rect.width() - page_label_width - bold_width) / 2;
        painter->setFont(bold_font);
        painter->drawText(page_label_width + prefix_suffix_width, option.rect.y() + y_offset, bold_text);

        painter->setFont(default_font);
        QString const suffix = font_metrics.elidedText(display_text.mid(bold_end + 4), Qt::ElideRight, prefix_suffix_width);
        painter->drawText(page_label_width + prefix_suffix_width + bold_width, option.rect.y() + y_offset, suffix);

        QString const prefix = font_metrics.elidedText(display_text.left(bold_begin - 3), Qt::ElideLeft, prefix_suffix_width);
        painter->drawText(
            page_label_width + prefix_suffix_width - font_metrics.horizontalAdvance(prefix),
            option.rect.y() + y_offset,
            prefix
        );
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}
}  // namespace widget_viewer
