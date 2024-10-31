#include "productivityReport.h"
#include "../include/task.h"
#include <iostream>
#include <QPdfWriter>
#include <QPainter>
#include <algorithm>

ProductivityReport::ProductivityReport(const QList<TaskPtr>& tasks, QObject* parent)
    : QObject(parent), m_tasks(tasks), m_completionRate(0), m_completedTasks(0), m_totalTasks(0) {}

double ProductivityReport::completionRate() const {
    return m_completionRate;
}

int ProductivityReport::completedTasks() const {
    return m_completedTasks;
}

int ProductivityReport::totalTasks() const {
    return m_totalTasks;
}

void ProductivityReport::gatherData() {
}

void ProductivityReport::analyzeData() {
    std::cout << "Analyser les données de productivité...\n";
    m_totalTasks = m_tasks.size();
    m_completedTasks = std::count_if(m_tasks.begin(), m_tasks.end(), [](const TaskPtr& task) {
        return task->getStatus() == Task::Status::Completed;
    });

    if (m_totalTasks > 0) {
        m_completionRate = (static_cast<double>(m_completedTasks) / m_totalTasks) * 100;
    } else {
        m_completionRate = 0;
    }
    // qDebug() << "Here";

    emit totalTasksChanged();
    emit completedTasksChanged();
    emit completionRateChanged();
}

void ProductivityReport::formatReport() {
    qDebug() << "Productivity Report:";
    qDebug() << "Total Tasks: " << m_totalTasks;
    qDebug() << "Completed Tasks: " << m_completedTasks;
    qDebug() << "Completion Rate: " << m_completionRate << "%";
}

// void ProductivityReport::generatePdfReport(const QString& filename) {
//     // Create a QPdfWriter instance
//     QPdfWriter pdfWriter(filename);
//     pdfWriter.setResolution(300); // Set the resolution of the PDF
//     pdfWriter.setPageSize(QPageSize::A4); // Set page size

//     // Create a QPainter to paint on the PDF
//     QPainter painter;
//     if (!painter.begin(&pdfWriter)) {
//         qWarning("Failed to open file for writing");
//         return;
//     }

//     painter.setPen(Qt::black);
//     painter.setFont(QFont("Arial", 12));

//     // Add total tasks
//     QString totalTasksText = QString("Total des tâches: %1").arg(m_totalTasks);
//     painter.drawText(50, 50, totalTasksText);

//     // Add completed tasks
//     QString completedTasksText = QString("Tâches complétées: %1").arg(m_completedTasks);
//     painter.drawText(50, 80, completedTasksText);

//     // Add completion rate
//     QString completionRateText = QString("Taux d'accomplissement: %1%").arg(m_completionRate);
//     painter.drawText(50, 110, completionRateText);

//     // Finalize the PDF document
//     painter.end();
// }
