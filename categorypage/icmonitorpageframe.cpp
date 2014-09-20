#include <QApplication>
#include "icmonitorpageframe.h"
#include "ui_icmonitorpageframe.h"
#include "iciopoint.h"
#include "iciomonitorpagebase.h"
#include "config.h"

ICMonitorPageFrame::ICMonitorPageFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ICMonitorPageFrame)
{
    ui->setupUi(this);
    otherPageLeft_ = new ICIOMonitorPageBase();
    otherPageRight_ = new ICIOMonitorPageBase();
    euPageLeft_ = new ICIOMonitorPageBase();
    euPageRight_ = new ICIOMonitorPageBase();
    Init_();
}

ICMonitorPageFrame::~ICMonitorPageFrame()
{
    delete ui;
}

void ICMonitorPageFrame::changeEvent(QEvent *e)
{
    QFrame::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        Init_();
        break;
    default:
        break;
    }
}

void ICMonitorPageFrame::Init_()
{
    ui->icMonitorFrameleft->Clear();
    ui->icMonitorFrameRight->Clear();
    QList<ICIOPoint> points;
    points.append(ICIOPoint("X010", tr("Z Balance"), 0));
    points.append(ICIOPoint("X011", tr("Main Start"), 1));
    points.append(ICIOPoint("X012", tr("Sub Start"), 2));//夹1确认限
    points.append(ICIOPoint("X013", tr("Main Shot-1"), 3));
    points.append(ICIOPoint("X014", tr("Main Shot-2"), 4));
    points.append(ICIOPoint("X015", tr("Main Shot-3"), 5));//吸1确认限
    points.append(ICIOPoint("X016", tr("Sub Shot-1"), 6));
    points.append(ICIOPoint("X017", tr("Sub Shot-2"), 7));

    points.append(ICIOPoint("X020", tr("Sub Shot-3"), 8));
    points.append(ICIOPoint("X021", tr("Main Clear-1"), 9));
    points.append(ICIOPoint("X022", tr("Main Clear-2"), 10));
    points.append(ICIOPoint("X023", tr("Main clear-3"), 11));
    points.append(ICIOPoint("X024", tr("Sub clear-1"), 12));
    points.append(ICIOPoint("X025", tr("Sub clear-2"), 13));
//    points.append(ICIOPoint("X026", tr("Reserve"), 14));
    points.append(ICIOPoint("X026", tr("Sub clear-3"), 14));
    points.append(ICIOPoint("X027", tr("Reserve-1"), 15));

    points.append(ICIOPoint("X030", tr("Reserve-2"), 16));
    points.append(ICIOPoint("X031", tr("Reserve-3"), 17));
    points.append(ICIOPoint("X032", tr("Reserve-4"), 18));
    points.append(ICIOPoint("X033", tr("Reserve-5"), 19));
    points.append(ICIOPoint("X034", tr("Reserve-6"), 20));
    points.append(ICIOPoint("X035", tr("X035"), 21));
    points.append(ICIOPoint("X036", tr("X036"), 22));
    points.append(ICIOPoint("X037", tr("X037"), 23));

    points.append(ICIOPoint("X040", tr("X1 Origin"), 24));
    points.append(ICIOPoint("X041", tr("Y1 Origin"), 25));
    points.append(ICIOPoint("X042", tr("Z Origin"), 26));
    points.append(ICIOPoint("X043", tr("X2 Origin"), 27));
    points.append(ICIOPoint("X044", tr("Y2 Origin"), 28));
    points.append(ICIOPoint("X045", tr("X045"), 29));
    points.append(ICIOPoint("X046", tr("X046"), 30));
    points.append(ICIOPoint("X047", tr("X047"), 31));

//    points.append(ICIOPoint("X050", tr("X1 Servo Alarm"), 48));
//    points.append(ICIOPoint("X051", tr("Y1 Servo Alarm"), 49));
//    points.append(ICIOPoint("X052", tr("Z Servo Alarm"), 50));
//    points.append(ICIOPoint("X053", tr("X2 Servo Alarm"), 51));
//    points.append(ICIOPoint("X054", tr("Y2 Servo Alarm"), 52));
//    points.append(ICIOPoint("X055", tr("A Servo Alarm"), 53));
//    points.append(ICIOPoint("X056", tr("B Servo Alarm"), 54));
//    points.append(ICIOPoint("X057", tr("C Servo Alarm"), 55));
    ui->icMonitorFrameleft->AddPage(otherPageLeft_, tr("Other"));
    ui->icMonitorFrameRight->AddPage(otherPageRight_, tr("Other"));
    otherPageLeft_->BindingPointsToInputPage(points);
    otherPageRight_->BindingPointsToInputPage(points);
    points.clear();

    points.append(ICIOPoint("Y010", tr("Y10"), 0));
    points.append(ICIOPoint("Y011", tr("Y11"), 1));
    points.append(ICIOPoint("Y012", tr("Y12"), 2));  //夹1阀
    points.append(ICIOPoint("Y013", tr("Main Shot-1 Valve"), 3));
    points.append(ICIOPoint("Y014", tr("Main Shot-2 Valve"), 4));
    points.append(ICIOPoint("Y015", tr("Main Shot-3 Valve"), 5));
    points.append(ICIOPoint("Y016", tr("Sub Shot-1 Valve"), 6));
    points.append(ICIOPoint("Y017", tr("Sub Shot-2 Valve"), 7));

    points.append(ICIOPoint("Y020", tr("Sub Shot-3 Valve"), 8));
    points.append(ICIOPoint("Y021", tr("Main Clear-1 Valve"), 9));
    points.append(ICIOPoint("Y022", tr("Main Clear-2 Valve"), 10));//1
    points.append(ICIOPoint("Y023", tr("Main Clear-3 Valve"), 11));//备用输出2
    points.append(ICIOPoint("Y024", tr("Sub Clear-1 Valve"), 12));
    points.append(ICIOPoint("Y025", tr("Sub Clear-2 Valve"), 13));
    points.append(ICIOPoint("Y026", tr("Sub Clear-3 Valve"), 14));
    points.append(ICIOPoint("Y027", tr("Reserve-1 Valve"), 15));

    points.append(ICIOPoint("Y030", tr("Reserve-2 Valve"), 16));
    points.append(ICIOPoint("Y031", tr("Reserve-3 Valve"), 17));
    points.append(ICIOPoint("Y032", tr("Reserve-4 Valve"), 18));
    points.append(ICIOPoint("Y033", tr("Reserve-5 Valve"), 19));
    points.append(ICIOPoint("Y034", tr("Reserve-6 Valve"), 20));
    points.append(ICIOPoint("Y035", tr("Y035"), 21));//4
    points.append(ICIOPoint("Y036", tr("Y036"), 22));//3
    points.append(ICIOPoint("Y037", tr("Y037"), 23));

    points.append(ICIOPoint("Y040", tr("Y040"), 24));
    points.append(ICIOPoint("Y041", tr("Y041"), 25));
    points.append(ICIOPoint("Y042", tr("Y042"), 26));
    points.append(ICIOPoint("Y043", tr("Y043"), 27));
    points.append(ICIOPoint("Y044", tr("Y044"), 28));
    points.append(ICIOPoint("Y045", tr("Y045"), 29));//4
    points.append(ICIOPoint("Y046", tr("Y046"), 30));//3
    points.append(ICIOPoint("Y047", tr("Y047"), 31));
//#ifdef HC_8AXIS
//    points.append(ICIOPoint("Y022", tr("Reserve 1"), 10));//1
//    points.append(ICIOPoint("Y023", tr("Reserve 2"), 11));//2
//    points.append(ICIOPoint("Y032", tr("Reserve 3"), 18));
//    points.append(ICIOPoint("Y033", tr("Reserve 4"), 19));
//    points.append(ICIOPoint("Y035", tr("Reserve 5"), 21));//4
//    points.append(ICIOPoint("Y036", tr("Reserve 6"), 22));//3
//#endif
    otherPageLeft_->BindingPointsToOutpuPage(points);
    otherPageRight_->BindingPointsToOutpuPage(points);

    ui->icMonitorFrameleft->AddPage(euPageLeft_, tr("EU"));
    ui->icMonitorFrameRight->AddPage(euPageRight_, tr("EU"));

    points.clear();
    points.append(ICIOPoint("", tr("Mold Opened"), 35));
    points.append(ICIOPoint("", tr("Mold Closed"), 34));
    points.append(ICIOPoint("", tr("Eject Forward"), 39));
    points.append(ICIOPoint("", tr("Eject Backward"), 38));
//    points.append(ICIOPoint("", tr("Mode open In 2"), 46)); //开模2完
    points.append(ICIOPoint("", tr("Core 1 In"), 46)); //入芯1到位
    points.append(ICIOPoint("", tr("Core 1 Out"), 45));
    points.append(ICIOPoint("", tr("Core 2 In"), 44));
    points.append(ICIOPoint("", tr("Core 2 Out"), 43));

//    points.append(ICIOPoint("", tr("Safe Door 2"), 33));//安全门2
    points.append(ICIOPoint("", tr("IMM Reject"), 33));//不良品
    points.append(ICIOPoint("", tr("ZC5"), 42));
    points.append(ICIOPoint("", tr("ZC6"), 41));
    points.append(ICIOPoint("", tr("ZC7"), 40));
    points.append(ICIOPoint("", tr("Safe Door"), 32));
    points.append(ICIOPoint("", tr("ES"), 47));
    points.append(ICIOPoint("", tr("Mold Inter"), 36));
    points.append(ICIOPoint("", tr("IMM Auto"), 37));

    euPageLeft_->BindingPointsToInputPage(points);
    euPageRight_->BindingPointsToInputPage(points);

    points.clear();
    points.append(ICIOPoint("", tr("Mold Open Permit"), 38)); //允许开模
    points.append(ICIOPoint("", tr("Mold Close Permit"), 32));
    points.append(ICIOPoint("", tr("Eject Forward Permit"), 33));
//    points.append(ICIOPoint("", tr("Thimble Permit 1"), 33));
    points.append(ICIOPoint("", tr("Eject Backward Permit"), 37));
//    points.append(ICIOPoint("", tr("Thimble Permit 2"), 37));
//    points.append(ICIOPoint("", tr("Mode Close Permit 2"), 40));
    points.append(ICIOPoint("", tr("Core 1 In Permit"), 40));
    points.append(ICIOPoint("", tr("Core 1 Out Permit"), 46));
    points.append(ICIOPoint("", tr("Core 2 In Permit"), 41));
    points.append(ICIOPoint("", tr("Core 2 Out Permit"), 45));

    points.append(ICIOPoint("", tr("Robot"), 35));
    points.append(ICIOPoint("", tr("En C6"), 44));
    points.append(ICIOPoint("", tr("En C7"), 43));
    points.append(ICIOPoint("", tr("En A8"), 42));
//    points.append(ICIOPoint("", tr("Blank 0"), 34));
//    points.append(ICIOPoint("", tr("Blank 1"), 36));
//    points.append(ICIOPoint("", tr("Blank2"), 39));
//    points.append(ICIOPoint("", tr("Blank3"), 47));

    euPageLeft_->BindingPointsToOutpuPage(points);
    euPageRight_->BindingPointsToOutpuPage(points);
}
