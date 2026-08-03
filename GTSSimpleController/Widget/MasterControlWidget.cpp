#include "MasterControlWidget.h"
#include "../../GtsCore/GtsMgr.h"

CMasterControlWidget::CMasterControlWidget(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    ui.doubleSpinBox_Vel->setValue(0.5);
    ui.doubleSpinBoxs_Acc->setValue(0.1);
    ui.doubleSpinBoxs_Dec->setValue(0.1);

    // 配置所有轴状态指示灯 (radioButton, 只读显示)
    QRadioButton* row1[] = { ui.radioButton_servoEnable1, ui.radioButton_sevorAlarm1,
        ui.radioButton_nLimit1, ui.radioButton_pLimit1, ui.radioButton_motionErr1,
        ui.radioButton_motionSts1, ui.radioButton_eStop1, ui.radioButton_smoothStop1 };
    QRadioButton* row2[] = { ui.radioButton_servoEnable2, ui.radioButton_sevorAlarm2,
        ui.radioButton_nLimit2, ui.radioButton_pLimit2, ui.radioButton_motionErr2,
        ui.radioButton_motionSts2, ui.radioButton_eStop2, ui.radioButton_smoothStop2 };
    QRadioButton* row3[] = { ui.radioButton_servoEnable3, ui.radioButton_sevorAlarm3,
        ui.radioButton_nLimit3, ui.radioButton_pLimit3, ui.radioButton_motionErr3,
        ui.radioButton_motionSts3, ui.radioButton_eStop3, ui.radioButton_smoothStop3 };
    QRadioButton* row4[] = { ui.radioButton_servoEnable4, ui.radioButton_sevorAlarm4,
        ui.radioButton_nLimit4, ui.radioButton_pLimit4, ui.radioButton_motionErr4,
        ui.radioButton_motionSts4, ui.radioButton_eStop4, ui.radioButton_smoothStop4 };
    QRadioButton** rows[] = { row1, row2, row3, row4 };

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 8; ++j) {
            rows[i][j]->setAutoExclusive(false);
            rows[i][j]->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        }
    }
}

CMasterControlWidget::~CMasterControlWidget()
{
    m_gtsMgr = nullptr;
}

void CMasterControlWidget::setGtsTotalMgr(GtsMgr* mgr)
{
    if (m_gtsMgr) {
        disconnect(m_gtsMgr, &GtsMgr::axisUpdated, this, &CMasterControlWidget::onAxisUpdated);
    }
    m_gtsMgr = mgr;
    if (m_gtsMgr) {
        connect(m_gtsMgr, &GtsMgr::axisUpdated, this, &CMasterControlWidget::onAxisUpdated);
        connect(m_gtsMgr, &GtsMgr::configChanged, this, [this]() {
            if (!m_connectionsInitialized) {
                initConnections();
                m_connectionsInitialized = true;
            }
        });
    }
}

void CMasterControlWidget::initConnections()
{
    // 用 ConfigMgr 轴名填充 comboBox
    ui.comboBox_axisID->clear();
    int count = m_gtsMgr ? m_gtsMgr->axisCount() : 0;
    for (short i = 1; i <= count; ++i) {
        AxisName name = m_gtsMgr->axisCfg()->axes[i - 1].name;
        QString label;
        switch (name) {
        case AxisName::X: label = QStringLiteral("X"); break;
        case AxisName::Y: label = QStringLiteral("Y"); break;
        case AxisName::Z: label = QStringLiteral("Z"); break;
        case AxisName::A: label = QStringLiteral("A"); break;
        default: label = QStringLiteral("?"); break;
        }
        ui.comboBox_axisID->addItem(label);
    }

    connect(ui.comboBox_axisID, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, [this](int index) { m_axisId = index + 1; });

    // 用 axisIdByName 动态查找各轴
    short idX = axisIdByName(AxisName::X);
    short idY = axisIdByName(AxisName::Y);
    short idZ = axisIdByName(AxisName::Z);
    short idA = axisIdByName(AxisName::A);

    if (idX > 0) {
        connect(ui.toolButton_Plus1, &QToolButton::pressed, this, [this, idX]() { onJogPressed(idX, 1); });
        connect(ui.toolButton_Plus1, &QToolButton::released, this, [this, idX]() { onJogReleased(idX); });
        connect(ui.toolButton_Minus1, &QToolButton::pressed, this, [this, idX]() { onJogPressed(idX, -1); });
        connect(ui.toolButton_Minus1, &QToolButton::released, this, [this, idX]() { onJogReleased(idX); });
        connect(ui.pushButtonHome1, &QPushButton::clicked, this, [this, idX]() { onHome(idX); });
    }
    if (idY > 0) {
        connect(ui.toolButton_Plus2, &QToolButton::pressed, this, [this, idY]() { onJogPressed(idY, 1); });
        connect(ui.toolButton_Plus2, &QToolButton::released, this, [this, idY]() { onJogReleased(idY); });
        connect(ui.toolButton_Minus2, &QToolButton::pressed, this, [this, idY]() { onJogPressed(idY, -1); });
        connect(ui.toolButton_Minus2, &QToolButton::released, this, [this, idY]() { onJogReleased(idY); });
        connect(ui.pushButtonHome2, &QPushButton::clicked, this, [this, idY]() { onHome(idY); });
    }
    if (idZ > 0) {
        connect(ui.toolButton_Plus3, &QToolButton::pressed, this, [this, idZ]() { onJogPressed(idZ, 1); });
        connect(ui.toolButton_Plus3, &QToolButton::released, this, [this, idZ]() { onJogReleased(idZ); });
        connect(ui.toolButton_Minus3, &QToolButton::pressed, this, [this, idZ]() { onJogPressed(idZ, -1); });
        connect(ui.toolButton_Minus3, &QToolButton::released, this, [this, idZ]() { onJogReleased(idZ); });
        connect(ui.pushButtonHome3, &QPushButton::clicked, this, [this, idZ]() { onHome(idZ); });
    }
    if (idA > 0) {
        connect(ui.toolButton_Plus4, &QToolButton::pressed, this, [this, idA]() { onJogPressed(idA, 1); });
        connect(ui.toolButton_Plus4, &QToolButton::released, this, [this, idA]() { onJogReleased(idA); });
        connect(ui.toolButton_Minus4, &QToolButton::pressed, this, [this, idA]() { onJogPressed(idA, -1); });
        connect(ui.toolButton_Minus4, &QToolButton::released, this, [this, idA]() { onJogReleased(idA); });
        connect(ui.pushButtonHome4, &QPushButton::clicked, this, [this, idA]() { onHome(idA); });
    }

    connect(ui.toolButton_Stop, &QToolButton::clicked, this, &CMasterControlWidget::onStopAll);
    connect(ui.pushButton_ActMotion, &QPushButton::clicked, this, &CMasterControlWidget::onActMotion);
}

void CMasterControlWidget::onJogPressed(short axisId, int direction)
{
    if (!m_gtsMgr) return;
    int index = axisId - 1;
    auto& jp = m_gtsMgr->axisCfg()->axes[index].jogParam;
    bool ok = m_gtsMgr->motionMgr()->setJogParam(axisId, jp);
    if (!ok) return;
    m_gtsMgr->motionMgr()->startJogMotion(axisId, direction);
}

void CMasterControlWidget::onJogReleased(short axisId)
{
    if (!m_gtsMgr) return;
    m_gtsMgr->axisMgr()->stop(axisId, 0);
}

void CMasterControlWidget::onStopAll()
{
    if (!m_gtsMgr) return;
    for (short id = 1; id <= m_gtsMgr->axisCount(); ++id) {
        m_gtsMgr->axisMgr()->stop(id, 0);
    }
}

void CMasterControlWidget::onHome(short axisId)
{
    if (!m_gtsMgr) return;
    m_gtsMgr->motionMgr()->homeStart(axisId);
}

void CMasterControlWidget::onActMotion()
{
    if (!m_gtsMgr) return;
    int index = m_axisId - 1;
    auto& tp = m_gtsMgr->axisCfg()->axes[index].trapParam;
    tp.motionVel = ui.doubleSpinBox_Vel->value();
    tp.acc = ui.doubleSpinBoxs_Acc->value();
    tp.dec = ui.doubleSpinBoxs_Dec->value();
    tp.lengthMm = ui.spinBox_trapStepSize1->value();
    m_gtsMgr->motionMgr()->setTrapParam(m_axisId, tp);
    m_gtsMgr->motionMgr()->trapMotion(m_axisId, tp.lengthMm);
}

void CMasterControlWidget::onAxisUpdated(const std::vector<SingleAxisInfo>& axisInfo)
{
    auto updateOneAxis = [this](const SingleAxisInfo& axis,
        QRadioButton* servoEnable, QRadioButton* alarm,
        QRadioButton* nLimit, QRadioButton* pLimit,
        QRadioButton* motionErr, QRadioButton* motionSts,
        QRadioButton* eStop, QRadioButton* smoothStop,
        QLabel* actPos, QLabel* actVel,
        QLabel* tgtPos, QLabel* tgtVel, QLabel* tgtAcc,
        QLabel* tgtPosPulse, QLabel* tgtVelPulse, QLabel* tgtAccPulse)
    {
        servoEnable->setChecked(axis.isServoOn);
        alarm->setChecked(axis.isAlarm);
        nLimit->setChecked(axis.isNegLimit);
        pLimit->setChecked(axis.isPosLimit);
        motionErr->setChecked(axis.isMError);
        motionSts->setChecked(axis.isMotion);
        eStop->setChecked(axis.isAbruptStop);
        smoothStop->setChecked(axis.isSmoothStop);
        actPos->setText(QString::number(axis.encPosMm, 'f', 3));
        actVel->setText(QString::number(axis.encVelMm, 'f', 3));
        tgtPos->setText(QString::number(axis.prfPosMm, 'f', 3));
        tgtVel->setText(QString::number(axis.prfVelMm, 'f', 3));
        tgtAcc->setText(QString::number(axis.prfAccMm, 'f', 3));
        tgtPosPulse->setText(QString::number(axis.prfPosOriginal, 'f', 3));
        tgtVelPulse->setText(QString::number(axis.prfVelOriginal, 'f', 3));
        tgtAccPulse->setText(QString::number(axis.prfAccOriginal, 'f', 3));
    };

    if ((int)axisInfo.size() >= 1)
        updateOneAxis(axisInfo[0],
            ui.radioButton_servoEnable1, ui.radioButton_sevorAlarm1,
            ui.radioButton_nLimit1, ui.radioButton_pLimit1,
            ui.radioButton_motionErr1, ui.radioButton_motionSts1,
            ui.radioButton_eStop1, ui.radioButton_smoothStop1,
            ui.label_actPosData1, ui.label_actVelData1,
            ui.label_tgtPosData1, ui.label_tgtVelData1, ui.label_tgtAccData1,
            ui.label_tgtPosDataPluse1, ui.label_tgtVelDataPluse1, ui.label_tgtAccDataPluse1);
    if ((int)axisInfo.size() >= 2)
        updateOneAxis(axisInfo[1],
            ui.radioButton_servoEnable2, ui.radioButton_sevorAlarm2,
            ui.radioButton_nLimit2, ui.radioButton_pLimit2,
            ui.radioButton_motionErr2, ui.radioButton_motionSts2,
            ui.radioButton_eStop2, ui.radioButton_smoothStop2,
            ui.label_actPosData2, ui.label_actVelData2,
            ui.label_tgtPosData2, ui.label_tgtVelData2, ui.label_tgtAccData2,
            ui.label_tgtPosDataPluse2, ui.label_tgtVelDataPluse2, ui.label_tgtAccDataPluse2);
    if ((int)axisInfo.size() >= 3)
        updateOneAxis(axisInfo[2],
            ui.radioButton_servoEnable3, ui.radioButton_sevorAlarm3,
            ui.radioButton_nLimit3, ui.radioButton_pLimit3,
            ui.radioButton_motionErr3, ui.radioButton_motionSts3,
            ui.radioButton_eStop3, ui.radioButton_smoothStop3,
            ui.label_actPosData3, ui.label_actVelData3,
            ui.label_tgtPosData3, ui.label_tgtVelData3, ui.label_tgtAccData3,
            ui.label_tgtPosDataPluse3, ui.label_tgtVelDataPluse3, ui.label_tgtAccDataPluse3);
    if ((int)axisInfo.size() >= 4)
        updateOneAxis(axisInfo[3],
            ui.radioButton_servoEnable4, ui.radioButton_sevorAlarm4,
            ui.radioButton_nLimit4, ui.radioButton_pLimit4,
            ui.radioButton_motionErr4, ui.radioButton_motionSts4,
            ui.radioButton_eStop4, ui.radioButton_smoothStop4,
            ui.label_actPosData4, ui.label_actVelData4,
            ui.label_tgtPosData4, ui.label_tgtVelData4, ui.label_tgtAccData4,
            ui.label_tgtPosDataPluse4, ui.label_tgtVelDataPluse4, ui.label_tgtAccDataPluse4);
}

short CMasterControlWidget::axisIdByName(AxisName name) const
{
    if (!m_gtsMgr) return 0;
    auto* cfg = m_gtsMgr->axisCfg();
    for (int i = 0; i < (int)cfg->axes.size(); ++i) {
        if (cfg->axes[i].name == name)
            return static_cast<short>(i + 1);
    }
    return 0;
}
