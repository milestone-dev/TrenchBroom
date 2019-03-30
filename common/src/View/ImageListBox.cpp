/*
 Copyright (C) 2010-2017 Kristian Duske

 This file is part of TrenchBroom.

 TrenchBroom is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 TrenchBroom is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with TrenchBroom. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ImageListBox.h"

#include "View/ViewConstants.h"
#include "View/wxUtils.h"

#include <wx/panel.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <QLabel>
#include <wx/statbmp.h>

#include <cassert>

namespace TrenchBroom {
    namespace View {
        ImageListBox::ImageListBox(QWidget* parent, const QString& emptyText) :
        ControlListBox(parent, true, emptyText) {
            InheritAttributes();
        }

        class ImageListBox::ImageListBoxItem : public Item {
        private:
            QLabel* m_titleText;
            QLabel* m_subtitleText;
            wxStaticBitmap* m_imageBmp;
        public:
            ImageListBoxItem(QWidget* parent, const wxSize& margins, const QString& title, const QString& subtitle) :
            Item(parent),
            m_titleText(nullptr),
            m_subtitleText(nullptr),
            m_imageBmp(nullptr) {
                InheritAttributes();
                createGui(margins, title, subtitle, nullptr);
            }

            ImageListBoxItem(QWidget* parent, const wxSize& margins, const QString& title, const QString& subtitle, const wxBitmap& image)  :
            Item(parent),
            m_titleText(nullptr),
            m_subtitleText(nullptr),
            m_imageBmp(nullptr) {
                InheritAttributes();
                createGui(margins, title, subtitle, &image);
            }

            void setDefaultColours(const wxColour& foreground, const wxColour& background) override {
                Item::setDefaultColours(foreground, background);
                m_subtitleText->SetForegroundColour(makeLighter(m_subtitleText->GetForegroundColour()));
            }
        private:
            void createGui(const wxSize& margins, const QString& title, const QString& subtitle, const wxBitmap* image) {
                m_titleText = new QLabel(this, wxID_ANY, title, wxDefaultPosition, wxDefaultSize,  wxST_ELLIPSIZE_END);
                m_subtitleText = new QLabel(this, wxID_ANY, subtitle, wxDefaultPosition, wxDefaultSize,  wxST_ELLIPSIZE_MIDDLE);

                m_titleText->SetFont(m_titleText->GetFont().Bold());
                m_subtitleText->SetForegroundColour(makeLighter(m_subtitleText->GetForegroundColour()));
#ifndef _WIN32
                m_subtitleText->SetWindowVariant(wxWINDOW_VARIANT_SMALL);
#endif

                auto* vSizer = new QVBoxLayout();
                vSizer->addWidget(m_titleText, 0);
                vSizer->addWidget(m_subtitleText, 0);

                auto* hSizer = new QHBoxLayout();
                hSizer->addSpacing(margins.x);

                if (image != nullptr) {
                    m_imageBmp = new wxStaticBitmap(this, wxID_ANY, *image);
                    hSizer->addWidget(m_imageBmp, 0, wxALIGN_BOTTOM | wxTOP | wxBOTTOM, margins.y);
                    hSizer->addSpacing(4);
                }
                hSizer->addWidget(vSizer, 0, wxTOP | wxBOTTOM, margins.y);
                hSizer->addSpacing(margins.x);

                setLayout(hSizer);
            }
        };

        ControlListBox::Item* ImageListBox::createItem(QWidget* parent, const wxSize& margins, const size_t index) {
            wxBitmap bitmap;
            if (image(index, bitmap)) {
                return new ImageListBoxItem(parent, margins, title(index), subtitle(index), bitmap);
            } else {
                return new ImageListBoxItem(parent, margins, title(index), subtitle(index));
            }
        }

        bool ImageListBox::image(const size_t n, wxBitmap& result) const {
            result = wxNullBitmap;
            return false;
        }
    }
}
