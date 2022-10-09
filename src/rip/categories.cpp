// SPDX-FileCopyrightText: 2005 Shaheed Haque (srhaque@iee.org). All rights reserved.
//
// SPDX-License-Identifier: GPL-2.0-or-later
//

#include "categories.h"

#include <KLocalizedString>

KCDDB::Categories::Categories()
{
    // These are only 11 Category values defined by CDDB. See
    //
    // http://www.freedb.org/en/faq.3.html#26
    //
    m_cddb << "blues" << "classical" << "country" <<
            "data" << "folk" << "jazz" << "misc" <<
            "newage" << "reggae" << "rock" << "soundtrack";
    m_i18n << i18n("Blues") << i18n("Classical") << i18nc("music genre", "Country") <<
            i18n("Data") << i18n("Folk") << i18n("Jazz") << i18n("Miscellaneous") <<
            i18n("New Age") << i18n("Reggae") << i18n("Rock") << i18n("Soundtrack");
}

const QString KCDDB::Categories::cddb2i18n(const QString &category) const
{
    int index = m_cddb.indexOf(category.trimmed());
    if (index != -1)
    {
        return m_i18n[index];
    }
    else
    {
        return cddb2i18n("misc");
    }
}

const QString KCDDB::Categories::i18n2cddb(const QString &category) const
{
    int index = m_i18n.indexOf(category.trimmed());
    if (index != -1)
    {
        return m_cddb[index];
    }
    else
    {
        return "misc";
    }
}
