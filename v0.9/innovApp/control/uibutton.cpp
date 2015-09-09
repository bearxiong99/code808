#include "uibutton.h"
//#include "guiconfig.h" 
#include <QPixmapCache>
/**************************************************************************************************
** 函数�? UIButton
**
** �? �? 构造函�?**
** �? �? QWidget *parent                  : 父窗�?**
** �? �? �?**
**************************************************************************************************/
UIButton::UIButton(QWidget *parent)
:QWidget(parent)
{
	m_bcheck = false;
	m_bfocus = false;
	//m_imgPath = GetHMICfg()->cResHmiFolder;

#if defined(QT_PLUGIN)
    m_imgPath = "../resource/";
#else
    m_imgPath = ":/";
#endif

	//setMouseTracking(true);//设置鼠标跟踪事件
	m_buttonState = BUTTON_NORMAL;
	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(LongPress()));
	update();
}

void UIButton::setvisible(const bool bvisibale)
{
	m_bvisibale = bvisibale;
	setVisible(m_bvisibale);
	update();
}

bool UIButton::isvisibale() const
{
	return m_bvisibale;
}

UIButton::~UIButton()
{

}

/**************************************************************************************************
** 函数�? mousePressEvent
**
** �? �? 鼠标按下事件
**
** �? �? QMouseEvent *                    : 鼠标事件
**
** �? �? �?**
**************************************************************************************************/
void UIButton::mousePressEvent(QMouseEvent *)
{
	if (BUTTON_DISABLE != m_buttonState)
	{
		m_buttonState = BUTTON_PRESS;
		m_timer->start(2000);
		repaint();
	}
}

/**************************************************************************************************
** 函数�? mouseReleaseEvent
**
** �? �? 鼠标释放事件
**
** �? �? QMouseEvent *                    : 鼠标事件
**
** �? �? �?**
**************************************************************************************************/
void UIButton::mouseReleaseEvent(QMouseEvent *)
{
	if (BUTTON_DISABLE != m_buttonState && BUTTON_NORMAL != m_buttonState)
	{
		m_buttonState = BUTTON_RELEASE;
		if (m_timer->isActive())
			m_timer->stop();
		if (isEnabled())
		{
			emit(clicked());
		}
		update();
	}
}

/**************************************************************************************************
** 函数�? mouseMoveEvent
**
** �? �? 鼠标移动事件
**
** �? �? QMouseEvent *                    : 鼠标事件
**
** �? �? �?**
**************************************************************************************************/
void UIButton::mouseMoveEvent(QMouseEvent *e)
{
	if (BUTTON_DISABLE != m_buttonState)
	{
		QRect rc;
		QPoint p;
		QMouseEvent *mouseEvent=NULL;

		if (QMouseEvent::MouseMove == e->type())
		{
			mouseEvent = (QMouseEvent *)e;

			if (mouseEvent->buttons() & Qt::LeftButton)
			{
				//p = e->pos();
				//rc = this->rect();
				//鼠标移动在区域内

				/*//异形控件响应的实�?				QPixmap m_bkimg;
				QBitmap bm(m_bkimg.mask());
				QRegion region(bm);
				region.contains(e->pos())*/
				if(this->rect().contains(e->pos()))
					// 				if (((rc.x() <= p.x()) && ((rc.x() + rc.width()) >= p.x()))&&
					// 					((rc.y() <= p.y()) && (rc.y() + rc.height()) >= p.y()))
				{
					m_buttonState = BUTTON_PRESSMOVE;
				}
				else
				{
					if (m_timer->isActive())
						m_timer->stop();
					m_buttonState = BUTTON_NORMAL;
				}

				update();
			}
		}
		//emit move(p);
	}
}

/**************************************************************************************************
** 函数�? enterEvent
**
** �? �? 当鼠标移入到按钮内时，更新按钮图�?**
** �? �? QMouseEvent *                    : 鼠标事件
**
** �? �? �?**
**************************************************************************************************/
void UIButton::enterEvent(QEvent *)
{
	if (BUTTON_DISABLE != m_buttonState)
	{
		m_buttonState = BUTTON_MOVE;

		update();
	}
}

/**************************************************************************************************
** 函数�? leaveEvent
**
** �? �? 当鼠标移出到按钮以外时，更新按钮图标
**
** �? �? QMouseEvent *                    : 鼠标事件
**
** �? �? �?**
**************************************************************************************************/
void UIButton::leaveEvent(QEvent *)
{
	if (BUTTON_DISABLE != m_buttonState)
	{
		m_buttonState = BUTTON_NORMAL;

		update();
	}
}

void UIButton::uncheck()
{
	setChecked(false);
}

/**************************************************************************************************
** 函数�? setNormalIcon
**
** �? �? 设置按钮正常状态下的图�?**
** �? �? const QString &normalIconName    : 图标路径
**
** �? �? �?**
**************************************************************************************************/
void UIButton::setNormalIcon(const QString &imgName)
{
	if (!imgName.isEmpty())
	{
		m_sIconnormal = imgName;
		if (!QPixmapCache::find(m_imgPath + m_sIconnormal, m_normalIconimg)) {
			m_normalIconimg.load(m_imgPath + m_sIconnormal);
			QPixmapCache::insert(m_imgPath + m_sIconnormal, m_normalIconimg);
		}
		//m_normalIconimg.load(m_imgPath + m_sIconnormal);
	}
	update();
}

QString UIButton::NormalIcon() const
{
	return m_sIconnormal;
}

void UIButton::setPressIcon(const QString &imgName)
{
	if (!imgName.isEmpty())
	{
		m_sIconpress = imgName;
		if (!QPixmapCache::find(m_imgPath + m_sIconpress, m_pressIconimg)) {
			m_pressIconimg.load(m_imgPath + m_sIconpress);
			QPixmapCache::insert(m_imgPath + m_sIconpress, m_pressIconimg);
		}
		//m_pressIconimg.load(m_imgPath + m_sIconpress);

	}
	update();
}

QString UIButton::PressIcon() const
{
	return m_sIconpress;
}
/**************************************************************************************************
** 函数�? setPressIcon
**
** �? �? 设置按钮被按下状态下的图�?**
** �? �? const QString &pressIconName     : 图标路径
**
** �? �? �?**
**************************************************************************************************/
void UIButton::setDisableIcon(const QString &imgName)
{
	if (!imgName.isEmpty())
	{
		m_sIcondisable = imgName;
		if (!QPixmapCache::find(m_imgPath + m_sIcondisable, m_disableIconimg)) {
			m_disableIconimg.load(m_imgPath + m_sIcondisable);
			QPixmapCache::insert(m_imgPath + m_sIcondisable, m_disableIconimg);
		}
		//m_disableIconimg.load(m_imgPath + m_sIcondisable);

	}
	update();

}

QString UIButton::DisableIcon() const
{
	return m_sIcondisable;
}


/**************************************************************************************************
** 函数�? setMoveIcon
**
** �? �? 设置鼠标在按钮上移动状态下的图�?**
** �? �? const QString &moveIconName      : 图标路径
**
** �? �? �?**
**************************************************************************************************/
void UIButton::setNormalBk(const QString &imgName)
{
	if (!imgName.isEmpty())
	{
		m_sBgnormal = imgName;
		if (!QPixmapCache::find(m_imgPath + m_sBgnormal, m_normalBkimg)) {
			m_normalBkimg.load(m_imgPath + m_sBgnormal);
			QPixmapCache::insert(m_imgPath + m_sBgnormal, m_normalBkimg);
		}
		//m_normalBkimg.load(m_imgPath + m_sBgnormal);
	}
	update();

}

QString UIButton::NormalBk() const
{
	return m_sBgnormal;
}

void UIButton::setPressBk(const QString &imgName)
{
	if (!imgName.isEmpty())
	{
		m_sBgpress = imgName;
		if (!QPixmapCache::find(m_imgPath + m_sBgpress, m_pressBkimg)) {
			m_pressBkimg.load(m_imgPath + m_sBgpress);
			QPixmapCache::insert(m_imgPath + m_sBgpress, m_pressBkimg);
		}
		//m_pressBkimg.load(m_imgPath + m_sBgpress);
	}
	update();

}

QString UIButton::PressBk() const
{
	return m_sBgpress;
}

void UIButton::setDisableBk(const QString &imgName)
{
	if (!imgName.isEmpty())
	{
		m_sBgdisable = imgName;
		if (!QPixmapCache::find(m_imgPath + m_sBgdisable, m_disableBkimg)) {
			m_disableBkimg.load(m_imgPath + m_sBgdisable);
			QPixmapCache::insert(m_imgPath + m_sBgdisable, m_disableBkimg);
		}
		//m_disableBkimg.load(m_imgPath + m_sBgdisable);
	}
	update();

}

QString UIButton::DisableBk() const
{
	return m_sBgdisable;
}

void UIButton::setCheckedBk(const QString &imgName)
{
	if (!imgName.isEmpty())
	{
		m_sBgcheck = imgName;
		if (!QPixmapCache::find(m_imgPath + m_sBgcheck, m_checkBkimg)) {
			m_checkBkimg.load(m_imgPath + m_sBgcheck);
			QPixmapCache::insert(m_imgPath + m_sBgcheck, m_checkBkimg);
		}
		//m_checkBkimg.load(m_imgPath + m_sBgcheck);
	}
	update();

}

QString UIButton::CheckedBk() const
{
	return m_sBgcheck;
}

void UIButton::setIconRect(const QRect &rect)
{
	m_iconRect = rect;
	update();
}

QRect UIButton::IconRect() const
{
	return m_iconRect;
}

void UIButton::setTextRect(const QRect &rect)
{
	m_textRect = rect;
	update();
}

QRect UIButton::textRect() const
{
	return m_textRect;
}


void UIButton::setColor(const QColor &color)
{
	m_color = color;
	update();
}

QColor UIButton::color() const
{
	return m_color;
}

void UIButton::setDisableColor(const QColor &color)
{
	m_discolor = color;
	update();
}

QColor UIButton::disablecolor() const
{
	return m_discolor;
}

/**************************************************************************************************
** 函数�? enabled
**
** �? �? 设置按钮各种状�?使能/禁止)
**
** �? �? bool flg                         : false/true
**
** �? �? �?**
**************************************************************************************************/
void UIButton::enabled(bool flg)
{

	if (false == flg)
	{
		m_buttonState = BUTTON_DISABLE;
	}
	else
	{
		m_buttonState = BUTTON_NORMAL;
	}

	this->setEnabled(flg);
}

void UIButton::setChecked(bool flg)
{
	m_bcheck = flg;
	update();
}

bool UIButton::isChecked()
{
	return m_bcheck;
}

void UIButton::setFocused(bool flg)
{
	m_bfocus = flg;
	update();
}

bool UIButton::isFocused()
{
	return m_bfocus;
}

/**************************************************************************************************
** 函数�? setUIButtonSize
**
** �? �? 设置按钮位置
**
** �? �? const QRect &rc                  : 矩形区域
**
** �? �? �?**
**************************************************************************************************/
void UIButton::setUIButtonSize(const QRect &rc)
{
	this->setGeometry(rc);
}

/**************************************************************************************************
** 函数�? setUIButtonSize
**
** �? �? 设置按钮位置
**
** �? �? int x                            : 左上x
**         int y                            : 左上y
**         int width                        : �?**         int height                       : �?**
** �? �? �?**
**************************************************************************************************/
void UIButton::setUIButtonSize(int x, int y, int width, int height)
{
	this->setGeometry(x, y, width, height);
}

void UIButton::setResPath(const QString& path)
{
	m_imgPath = path;
}

QString UIButton::ResPath() const
{
	return m_imgPath;
}

void UIButton::setText(QString name)
{
	m_text = name;
	update();
}

QString UIButton::Text() const
{
	return m_text;
}

void UIButton::LongPress()
{
	if (m_timer->isActive())
		m_timer->stop();

	emit(LongPressed());
}

/**************************************************************************************************
** 函数�? paintEvent
**
** �? �? 重绘
**
** �? �? QPaintEvent *                    : 重绘事件
**
** �? �? �?**
**************************************************************************************************/
void UIButton::paintEvent(QPaintEvent *)
{
	if (!m_bvisibale)
	{
		return;
	}
	QRect rc;
	rc = this->rect();
	QPainter painter(this);

	painter.setRenderHint(QPainter::Antialiasing);

	if (BUTTON_PRESS == m_buttonState || BUTTON_PRESSMOVE == m_buttonState)//按下状�?	
	{
		if (m_bcheck && !m_checkBkimg.isNull())
		{
			painter.drawPixmap(0, 0, m_checkBkimg);
		}
		else if (m_bfocus && !m_pressBkimg.isNull())
		{
			painter.drawPixmap(0, 0, m_pressBkimg);
		}
		else
		{
			painter.drawPixmap(0, 0, m_pressBkimg);
		}
		if (m_bcheck)
		{
			if(m_iconRect.isValid())
				painter.drawPixmap(m_iconRect, m_pressIconimg);
			else
				painter.drawPixmap(0,0, m_pressIconimg);
		}
		else
		{
			if(m_iconRect.isValid())
				painter.drawPixmap(m_iconRect, m_normalIconimg);
			else
				painter.drawPixmap(0,0, m_normalIconimg);
		}
	}
	else if ((BUTTON_NORMAL == m_buttonState) || (BUTTON_RELEASE == m_buttonState))//释放或正常状�?	
	{
		if (m_bcheck && !m_checkBkimg.isNull())
		{
			painter.drawPixmap(0, 0, m_checkBkimg);
		}
		else if (m_bfocus && !m_pressBkimg.isNull())
		{
			painter.drawPixmap(0, 0, m_pressBkimg);
		}
		else
		{
			painter.drawPixmap(0, 0, m_normalBkimg);
		}

		if (m_bcheck)
		{
			if(m_iconRect.isValid())
				painter.drawPixmap(m_iconRect, m_pressIconimg);
			else
				painter.drawPixmap(0,0, m_pressIconimg);
		}
		else
		{
			if(m_iconRect.isValid())
				painter.drawPixmap(m_iconRect, m_normalIconimg);
			else
				painter.drawPixmap(0,0, m_normalIconimg);
		}
	}
	else if (BUTTON_MOVE == m_buttonState)//移动状�?	
	{
		if (m_bcheck && !m_checkBkimg.isNull())
		{
			painter.drawPixmap(0, 0, m_checkBkimg);
		}
		else if (m_bfocus && !m_pressBkimg.isNull())
		{
			painter.drawPixmap(0, 0, m_pressBkimg);
		}
		else
		{
			painter.drawPixmap(0, 0, m_normalBkimg);
		}
		if (m_bcheck)
		{
			if(m_iconRect.isValid())
				painter.drawPixmap(m_iconRect, m_pressIconimg);
			else
				painter.drawPixmap(0,0, m_pressIconimg);
		}
		else
		{
			if(m_iconRect.isValid())
				painter.drawPixmap(m_iconRect, m_normalIconimg);
			else
				painter.drawPixmap(0,0, m_normalIconimg);
		}
	}
	else if (BUTTON_DISABLE == m_buttonState)//禁止状�?	
	{
		painter.drawPixmap(0, 0, m_disableBkimg);
		if(m_iconRect.isValid())
			painter.drawPixmap(m_iconRect, m_disableIconimg);
		else
			painter.drawPixmap(0,0, m_disableIconimg);
	}
	if (!m_text.isEmpty())
	{
		if (this->isEnabled())
		{
			painter.setPen(QColor(m_color));
		}
		else
		{
			painter.setPen(QColor(m_discolor));
		}
		QFontMetrics fm(font());
		QString text2 = fm.elidedText(m_text, Qt::ElideRight, m_textRect.width());
		painter.drawText(m_textRect,m_textalign,text2);
	}

}

