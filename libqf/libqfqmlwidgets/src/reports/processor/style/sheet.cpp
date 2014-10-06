#include "sheet.h"

using namespace qf::qmlwidgets::reports::style;

Sheet::Sheet(QObject *parent)
	: QObject(parent)
{
	qfLogFuncFrame();
}

Sheet::~Sheet()
{
	qfLogFuncFrame();
	//qDeleteAll(m_colors); it seems that QQmlListProperty itself handles color children parentship
}

Pen *Sheet::penForName(const QString &name)
{
	Pen *ret = m_definedPens.value(name);
	QF_ASSERT(ret != nullptr, "Cannot find pen for name: " + name, return ret);
	return ret;
}

void Sheet::setPenForName(const QString &name, Pen *p)
{
	if(p)
		m_definedPens[name] = p;
	else
		m_definedPens.remove(name);
}

QQmlListProperty<Color> Sheet::colors()
{
	/// Generally this constructor should not be used in production code, as a writable QList violates QML's memory management rules. However, this constructor can be very useful while prototyping.
	return QQmlListProperty<Color>(this, m_colors);
}

QQmlListProperty<Pen> Sheet::pens()
{
	return QQmlListProperty<Pen>(this, m_pens);
}
