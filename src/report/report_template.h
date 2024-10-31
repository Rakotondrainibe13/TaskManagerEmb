#ifndef REPORT_TEMPLATE_H
#define REPORT_TEMPLATE_H

class ReportTemplate {
public:
    void generateReport() {
        gatherData();
        analyzeData();
        formatReport();
        distributeReport();
    }

protected:
    virtual void gatherData() = 0;
    virtual void analyzeData() = 0;
    virtual void formatReport() = 0;
    virtual void distributeReport() {
        // Implémentation par défaut
    }
};
#endif
