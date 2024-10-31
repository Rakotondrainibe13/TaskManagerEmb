
-- CREATE TABLE (06)
-- Table Tasks
CREATE TABLE Tasks (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    title VARCHAR(255) NOT NULL,
    description TEXT,
    status VARCHAR(50) NOT NULL,
    type VARCHAR(50) NOT NULL,
    priority INTEGER,
    due_date DATETIME,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    updated_at DATETIME DEFAULT CURRENT_TIMESTAMP
);

-- Table TaskDependencies
CREATE TABLE TaskDependencies (
    task_id INTEGER,
    dependency_id INTEGER,
    PRIMARY KEY (task_id, dependency_id),
    FOREIGN KEY (task_id) REFERENCES Tasks(id)
 ON DELETE CASCADE,
    FOREIGN KEY (dependency_id) REFERENCES Tasks(id)
 ON DELETE CASCADE
);

-- Table TaskImbrication  (
CREATE TABLE TaskImbrication  (
    task_id INTEGER,
    subtask_id INTEGER,
    PRIMARY KEY (task_id, subtask_id),
    FOREIGN KEY (task_id) REFERENCES Tasks(id)
 ON DELETE CASCADE,
    FOREIGN KEY (subtask_id) REFERENCES Tasks(id)
 ON DELETE CASCADE
);

-- Table Users
CREATE TABLE Users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username VARCHAR(50) UNIQUE NOT NULL,
    password_hash VARCHAR(255) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP
);

-- Table TaskAssignments
CREATE TABLE TaskAssignments (
    task_id INTEGER,
    user_id INTEGER,
    assigned_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY (task_id, user_id),
    FOREIGN KEY (task_id) REFERENCES Tasks(id) ON DELETE CASCADE,
    FOREIGN KEY (user_id) REFERENCES Users(id) ON DELETE CASCADE
);

-- Table Notifications
CREATE TABLE Notifications (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER,
    task_id INTEGER,
    message TEXT NOT NULL,
    is_read BOOLEAN DEFAULT FALSE,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES Users(id) ON DELETE CASCADE,
    FOREIGN KEY (task_id) REFERENCES Tasks(id) ON DELETE CASCADE
);

-- Table TaskExecutionLogs
CREATE TABLE TaskExecutionLogs (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    task_id INTEGER,
    execution_strategy VARCHAR(50),
    start_time DATETIME,
    end_time DATETIME,
    status VARCHAR(50),
    FOREIGN KEY (task_id) REFERENCES Tasks(id) ON DELETE CASCADE
);

-- Table SecurityLogs
CREATE TABLE SecurityLogs (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER,
    action VARCHAR(100) NOT NULL,
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    details TEXT,
    FOREIGN KEY (user_id) REFERENCES Users(id) ON DELETE SET NULL
);

-- Table Subscription Type
CREATE TABLE SubscriptionTypes (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    subscription_type_name VARCHAR(100) NOT NULL,
    price REAL NOT NULL,
    duration INTEGER NOT NULL -- En Jour
);

-- Table Subscription 
CREATE TABLE Subscriptions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER,
    subscription_type_id INTEGER,
    payment_method_id INTEGER,
    email_address VARCHAR(100),
    card_number VARCHAR(100),
    quantity INTEGER,
    start_date DATETIME NOT NULL,
    end_date DATETIME NOT NULL,
    price REAL NOT NULL, -- For denormalisation
    duration INTEGER NOT NULL,
    subscription_date DATETIME DEFAULT CURRENT_TIMESTAMP,
    status INTEGER,
    FOREIGN KEY (user_id) REFERENCES Users(id) ON DELETE SET NULL,
    FOREIGN KEY (subscription_type_id) REFERENCES SubscriptionTypes(id) ON DELETE SET NULL,
);


-- CREATE INDEX ()
-- on Table Tasks ()
CREATE INDEX idx_tasks_title ON Tasks(title);
-- on Table Users ()
CREATE INDEX idx_users_infos ON Users(username,email);
-- on Table TaskAssignments ()
CREATE INDEX idx_taskassignments_task_user ON TaskAssignments(task_id, user_id);
-- on Table Notifications ()
CREATE INDEX idx_notifications_user_id ON Notifications(user_id);
-- on Table TaskExecutionLogs ()
CREATE INDEX idx_taskexecutionlogs_task_id ON TaskExecutionLogs(task_id);
-- on Table SecurityLogs ()
CREATE INDEX idx_securitylogs_user_id ON SecurityLogs(user_id);
-- on Table Subscriptions ()
CREATE INDEX idx_subscriptions_user_id ON Subscriptions(user_id);
