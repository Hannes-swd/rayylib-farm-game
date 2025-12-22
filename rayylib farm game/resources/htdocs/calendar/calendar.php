<?php
session_start();

// Datenbank-Konfiguration
$db_host = 'localhost';
$db_name = 'calendar_db';
$db_user = 'root';
$db_pass = '';

// Datenbank-Verbindung
try {
    $pdo = new PDO("mysql:host=$db_host;dbname=$db_name;charset=utf8mb4", $db_user, $db_pass);
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
} catch(PDOException $e) {
    die("Datenbankverbindung fehlgeschlagen: " . $e->getMessage());
}

// Tabelle erstellen falls nicht vorhanden
$pdo->exec("CREATE TABLE IF NOT EXISTS events (
    id INT AUTO_INCREMENT PRIMARY KEY,
    title VARCHAR(255) NOT NULL,
    date DATE NOT NULL,
    time_start TIME NOT NULL,
    time_end TIME,
    color VARCHAR(7) DEFAULT '#3b82f6',
    description TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
)");

// AJAX Handler
if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['ajax'])) {
    header('Content-Type: application/json');
    
    if ($_POST['action'] === 'getEvents') {
        $start = $_POST['start'];
        $end = $_POST['end'];
        $stmt = $pdo->prepare("SELECT * FROM events WHERE date BETWEEN ? AND ? ORDER BY date, time_start");
        $stmt->execute([$start, $end]);
        echo json_encode($stmt->fetchAll(PDO::FETCH_ASSOC));
        exit;
    }
    
    if ($_POST['action'] === 'addEvent') {
        $stmt = $pdo->prepare("INSERT INTO events (title, date, time_start, time_end, color, description) VALUES (?, ?, ?, ?, ?, ?)");
        $stmt->execute([
            $_POST['title'],
            $_POST['date'],
            $_POST['time_start'],
            $_POST['time_end'] ?? null,
            $_POST['color'] ?? '#3b82f6',
            $_POST['description'] ?? ''
        ]);
        echo json_encode(['success' => true, 'id' => $pdo->lastInsertId()]);
        exit;
    }
    
    if ($_POST['action'] === 'deleteEvent') {
        $stmt = $pdo->prepare("DELETE FROM events WHERE id = ?");
        $stmt->execute([$_POST['id']]);
        echo json_encode(['success' => true]);
        exit;
    }
}

$today = date('Y-m-d');
?>
<!DOCTYPE html>
<html lang="de">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Professioneller Kalender</title>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.7.1/jquery.min.js"></script>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }

        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background: #f5f5f5;
            color: #333;
        }

        .container {
            display: flex;
            height: 100vh;
        }

        /* SIDEBAR */
        .sidebar {
            width: 320px;
            background: white;
            border-right: 1px solid #e0e0e0;
            display: flex;
            flex-direction: column;
            overflow-y: auto;
        }

        .sidebar-section {
            padding: 20px;
            border-bottom: 1px solid #e0e0e0;
        }

        .sidebar-section h3 {
            font-size: 14px;
            color: #666;
            margin-bottom: 15px;
            text-transform: uppercase;
            letter-spacing: 0.5px;
        }

        /* MINI KALENDER */
        .mini-calendar {
            background: white;
        }

        .mini-calendar-header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin-bottom: 15px;
        }

        .mini-calendar-header h4 {
            font-size: 16px;
            font-weight: 600;
        }

        .mini-nav-btn {
            background: none;
            border: none;
            cursor: pointer;
            padding: 5px 10px;
            border-radius: 4px;
            font-size: 18px;
            color: #666;
        }

        .mini-nav-btn:hover {
            background: #f0f0f0;
        }

        .mini-calendar-grid {
            display: grid;
            grid-template-columns: repeat(7, 1fr);
            gap: 2px;
        }

        .mini-weekday {
            text-align: center;
            font-size: 11px;
            color: #999;
            padding: 5px 0;
            font-weight: 600;
        }

        .mini-day {
            aspect-ratio: 1;
            display: flex;
            align-items: center;
            justify-content: center;
            font-size: 13px;
            cursor: pointer;
            border-radius: 50%;
            position: relative;
        }

        .mini-day:hover {
            background: #f0f0f0;
        }

        .mini-day.other-month {
            color: #ccc;
        }

        .mini-day.today {
            background: #3b82f6;
            color: white;
            font-weight: bold;
        }

        .mini-day.selected {
            background: #dbeafe;
            color: #1e40af;
            font-weight: bold;
        }

        .mini-day.has-events::after {
            content: '';
            position: absolute;
            bottom: 2px;
            width: 4px;
            height: 4px;
            background: #3b82f6;
            border-radius: 50%;
        }

        /* HEUTIGE TERMINE */
        .today-events {
            max-height: 300px;
            overflow-y: auto;
        }

        .today-event {
            padding: 10px;
            margin-bottom: 8px;
            border-radius: 6px;
            border-left: 4px solid;
            background: #f9fafb;
            cursor: pointer;
        }

        .today-event:hover {
            background: #f3f4f6;
        }

        .today-event-time {
            font-size: 12px;
            color: #666;
            font-weight: 600;
        }

        .today-event-title {
            font-size: 14px;
            margin-top: 4px;
        }

        /* SUCHE */
        .search-box {
            display: flex;
            gap: 8px;
        }

        .search-box input {
            flex: 1;
            padding: 10px;
            border: 1px solid #ddd;
            border-radius: 6px;
            font-size: 14px;
        }

        .search-box button {
            padding: 10px 16px;
            background: #3b82f6;
            color: white;
            border: none;
            border-radius: 6px;
            cursor: pointer;
            font-weight: 600;
        }

        .search-box button:hover {
            background: #2563eb;
        }

        /* MAIN BEREICH */
        .main-content {
            flex: 1;
            display: flex;
            flex-direction: column;
            background: white;
        }

        .toolbar {
            display: flex;
            justify-content: space-between;
            align-items: center;
            padding: 20px 30px;
            border-bottom: 1px solid #e0e0e0;
            background: white;
        }

        .toolbar-left {
            display: flex;
            gap: 15px;
            align-items: center;
        }

        .current-date {
            font-size: 24px;
            font-weight: 600;
            color: #1f2937;
        }

        .nav-buttons {
            display: flex;
            gap: 5px;
        }

        .nav-btn {
            padding: 8px 16px;
            background: white;
            border: 1px solid #ddd;
            border-radius: 6px;
            cursor: pointer;
            font-size: 14px;
        }

        .nav-btn:hover {
            background: #f9fafb;
        }

        .view-buttons {
            display: flex;
            gap: 5px;
            background: #f3f4f6;
            padding: 4px;
            border-radius: 8px;
        }

        .view-btn {
            padding: 8px 20px;
            background: transparent;
            border: none;
            border-radius: 6px;
            cursor: pointer;
            font-weight: 600;
            font-size: 14px;
            color: #666;
        }

        .view-btn.active {
            background: white;
            color: #3b82f6;
            box-shadow: 0 1px 3px rgba(0,0,0,0.1);
        }

        .calendar-view {
            flex: 1;
            overflow: auto;
            padding: 20px 30px;
        }

        /* TAGESANSICHT */
        .day-view {
            max-width: 800px;
            margin: 0 auto;
        }

        .time-slots {
            border: 1px solid #e0e0e0;
            border-radius: 8px;
            overflow: hidden;
        }

        .time-slot {
            display: grid;
            grid-template-columns: 80px 1fr;
            border-bottom: 1px solid #f0f0f0;
            min-height: 60px;
        }

        .time-slot:last-child {
            border-bottom: none;
        }

        .time-label {
            padding: 10px;
            text-align: right;
            font-size: 12px;
            color: #999;
            border-right: 1px solid #f0f0f0;
            background: #fafafa;
        }

        .time-content {
            padding: 5px 10px;
            cursor: pointer;
            position: relative;
        }

        .time-content:hover {
            background: #f9fafb;
        }

        .event-card {
            padding: 8px 12px;
            border-radius: 6px;
            margin: 5px 0;
            border-left: 4px solid;
            cursor: pointer;
            background: #f0f9ff;
        }

        .event-card:hover {
            box-shadow: 0 2px 8px rgba(0,0,0,0.1);
        }

        .event-time {
            font-size: 12px;
            font-weight: 600;
            color: #666;
        }

        .event-title {
            font-size: 14px;
            margin-top: 4px;
            font-weight: 600;
        }

        /* WOCHENANSICHT */
        .week-view {
            overflow-x: auto;
        }

        .week-grid {
            display: grid;
            grid-template-columns: 60px repeat(7, 1fr);
            min-width: 900px;
            border: 1px solid #e0e0e0;
            border-radius: 8px;
            overflow: hidden;
        }

        .week-header {
            padding: 15px 10px;
            text-align: center;
            border-bottom: 1px solid #e0e0e0;
            background: #fafafa;
            font-weight: 600;
        }

        .week-header.today-col {
            background: #dbeafe;
            color: #1e40af;
        }

        .week-day-name {
            font-size: 12px;
            color: #666;
            text-transform: uppercase;
        }

        .week-day-num {
            font-size: 20px;
            margin-top: 5px;
        }

        .week-time-label {
            padding: 10px;
            text-align: right;
            font-size: 11px;
            color: #999;
            border-right: 1px solid #f0f0f0;
            border-bottom: 1px solid #f0f0f0;
            background: #fafafa;
        }

        .week-time-cell {
            border-right: 1px solid #f0f0f0;
            border-bottom: 1px solid #f0f0f0;
            min-height: 50px;
            padding: 2px;
            cursor: pointer;
            position: relative;
        }

        .week-time-cell:hover {
            background: #f9fafb;
        }

        .week-time-cell.today-col {
            background: #f0f9ff;
        }

        .week-event {
            padding: 4px 6px;
            border-radius: 4px;
            font-size: 12px;
            margin: 2px 0;
            border-left: 3px solid;
            cursor: pointer;
            white-space: nowrap;
            overflow: hidden;
            text-overflow: ellipsis;
        }

        /* MONATSANSICHT */
        .month-view {
            max-width: 1400px;
            margin: 0 auto;
        }

        .month-grid {
            display: grid;
            grid-template-columns: repeat(7, 1fr);
            gap: 1px;
            background: #e0e0e0;
            border: 1px solid #e0e0e0;
            border-radius: 8px;
            overflow: hidden;
        }

        .month-weekday {
            padding: 12px;
            text-align: center;
            background: #fafafa;
            font-weight: 600;
            font-size: 13px;
            color: #666;
            text-transform: uppercase;
        }

        .month-day {
            background: white;
            min-height: 120px;
            padding: 8px;
            cursor: pointer;
        }

        .month-day:hover {
            background: #f9fafb;
        }

        .month-day.other-month {
            background: #f9fafb;
            color: #ccc;
        }

        .month-day.today {
            background: #dbeafe;
        }

        .month-day-num {
            font-size: 14px;
            font-weight: 600;
            margin-bottom: 8px;
        }

        .month-day.today .month-day-num {
            display: inline-block;
            background: #3b82f6;
            color: white;
            width: 28px;
            height: 28px;
            border-radius: 50%;
            text-align: center;
            line-height: 28px;
        }

        .month-events {
            display: flex;
            flex-direction: column;
            gap: 4px;
        }

        .month-event {
            padding: 4px 6px;
            border-radius: 4px;
            font-size: 11px;
            border-left: 3px solid;
            white-space: nowrap;
            overflow: hidden;
            text-overflow: ellipsis;
            cursor: pointer;
        }

        .month-event:hover {
            box-shadow: 0 1px 4px rgba(0,0,0,0.2);
        }

        .more-events {
            font-size: 11px;
            color: #666;
            margin-top: 4px;
            font-weight: 600;
        }

        /* MODAL */
        .modal {
            display: none;
            position: fixed;
            top: 0;
            left: 0;
            width: 100%;
            height: 100%;
            background: rgba(0,0,0,0.5);
            z-index: 1000;
            align-items: center;
            justify-content: center;
        }

        .modal.active {
            display: flex;
        }

        .modal-content {
            background: white;
            padding: 30px;
            border-radius: 12px;
            width: 500px;
            max-width: 90%;
            box-shadow: 0 20px 25px -5px rgba(0,0,0,0.1);
        }

        .modal-header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin-bottom: 20px;
        }

        .modal-header h2 {
            font-size: 20px;
        }

        .close-btn {
            background: none;
            border: none;
            font-size: 24px;
            cursor: pointer;
            color: #999;
        }

        .form-group {
            margin-bottom: 20px;
        }

        .form-group label {
            display: block;
            margin-bottom: 8px;
            font-weight: 600;
            font-size: 14px;
        }

        .form-group input,
        .form-group textarea,
        .form-group select {
            width: 100%;
            padding: 10px;
            border: 1px solid #ddd;
            border-radius: 6px;
            font-size: 14px;
            font-family: inherit;
        }

        .form-group textarea {
            resize: vertical;
            min-height: 80px;
        }

        .color-options {
            display: flex;
            gap: 10px;
        }

        .color-option {
            width: 40px;
            height: 40px;
            border-radius: 8px;
            cursor: pointer;
            border: 3px solid transparent;
        }

        .color-option.selected {
            border-color: #333;
        }

        .modal-buttons {
            display: flex;
            gap: 10px;
            justify-content: flex-end;
            margin-top: 25px;
        }

        .btn {
            padding: 10px 20px;
            border: none;
            border-radius: 6px;
            cursor: pointer;
            font-weight: 600;
            font-size: 14px;
        }

        .btn-primary {
            background: #3b82f6;
            color: white;
        }

        .btn-primary:hover {
            background: #2563eb;
        }

        .btn-secondary {
            background: #f3f4f6;
            color: #666;
        }

        .btn-secondary:hover {
            background: #e5e7eb;
        }

        .btn-danger {
            background: #ef4444;
            color: white;
        }

        .btn-danger:hover {
            background: #dc2626;
        }
    </style>
</head>
<body>
    <div class="container">
        <!-- SIDEBAR -->
        <div class="sidebar">
            <!-- Mini Kalender -->
            <div class="sidebar-section">
                <div class="mini-calendar">
                    <div class="mini-calendar-header">
                        <button class="mini-nav-btn" onclick="navigateMiniMonth(-1)">‹</button>
                        <h4 id="miniMonthYear"></h4>
                        <button class="mini-nav-btn" onclick="navigateMiniMonth(1)">›</button>
                    </div>
                    <div class="mini-calendar-grid" id="miniCalendar"></div>
                </div>
            </div>

            <!-- Heutige Termine -->
            <div class="sidebar-section">
                <h3>Heutige Termine</h3>
                <div class="today-events" id="todayEvents"></div>
            </div>

            <!-- Suche -->
            <div class="sidebar-section">
                <h3>Datum suchen</h3>
                <div class="search-box">
                    <input type="text" id="dateSearch" placeholder="TT.MM.JJJJ" maxlength="10">
                    <button onclick="searchDate()">Suchen</button>
                </div>
            </div>
        </div>

        <!-- MAIN CONTENT -->
        <div class="main-content">
            <!-- Toolbar -->
            <div class="toolbar">
                <div class="toolbar-left">
                    <h1 class="current-date" id="currentDate"></h1>
                    <div class="nav-buttons">
                        <button class="nav-btn" onclick="navigateView(-1)">‹ Zurück</button>
                        <button class="nav-btn" onclick="goToToday()">Heute</button>
                        <button class="nav-btn" onclick="navigateView(1)">Weiter ›</button>
                    </div>
                </div>
                <div class="view-buttons">
                    <button class="view-btn active" data-view="day" onclick="changeView('day')">Tag</button>
                    <button class="view-btn" data-view="week" onclick="changeView('week')">Woche</button>
                    <button class="view-btn" data-view="month" onclick="changeView('month')">Monat</button>
                </div>
            </div>

            <!-- Calendar View -->
            <div class="calendar-view" id="calendarView"></div>
        </div>
    </div>

    <!-- Event Modal -->
    <div class="modal" id="eventModal">
        <div class="modal-content">
            <div class="modal-header">
                <h2 id="modalTitle">Neuer Termin</h2>
                <button class="close-btn" onclick="closeModal()">×</button>
            </div>
            <form id="eventForm">
                <input type="hidden" id="eventId">
                <div class="form-group">
                    <label>Titel *</label>
                    <input type="text" id="eventTitle" required>
                </div>
                <div class="form-group">
                    <label>Datum *</label>
                    <input type="date" id="eventDate" required>
                </div>
                <div class="form-group">
                    <label>Start-Zeit *</label>
                    <input type="time" id="eventTimeStart" required>
                </div>
                <div class="form-group">
                    <label>End-Zeit</label>
                    <input type="time" id="eventTimeEnd">
                </div>
                <div class="form-group">
                    <label>Farbe</label>
                    <div class="color-options">
                        <div class="color-option selected" style="background: #3b82f6" data-color="#3b82f6"></div>
                        <div class="color-option" style="background: #10b981" data-color="#10b981"></div>
                        <div class="color-option" style="background: #f59e0b" data-color="#f59e0b"></div>
                        <div class="color-option" style="background: #ef4444" data-color="#ef4444"></div>
                        <div class="color-option" style="background: #8b5cf6" data-color="#8b5cf6"></div>
                    </div>
                </div>
                <div class="form-group">
                    <label>Beschreibung</label>
                    <textarea id="eventDescription"></textarea>
                </div>
                <div class="modal-buttons">
                    <button type="button" class="btn btn-danger" id="deleteBtn" style="display:none" onclick="deleteEvent()">Löschen</button>
                    <button type="button" class="btn btn-secondary" onclick="closeModal()">Abbrechen</button>
                    <button type="submit" class="btn btn-primary">Speichern</button>
                </div>
            </form>
        </div>
    </div>

    <script>
        // Globale Variablen
        let currentView = 'day';
        let currentDate = new Date();
        let miniCalendarDate = new Date();
        let selectedColor = '#3b82f6';
        let allEvents = [];

        // Deutsche Monatsnamen und Wochentage
        const monthNames = ['Januar', 'Februar', 'März', 'April', 'Mai', 'Juni', 
                           'Juli', 'August', 'September', 'Oktober', 'November', 'Dezember'];
        const dayNames = ['Sonntag', 'Montag', 'Dienstag', 'Mittwoch', 'Donnerstag', 'Freitag', 'Samstag'];
        const shortDayNames = ['So', 'Mo', 'Di', 'Mi', 'Do', 'Fr', 'Sa'];

        // Initialisierung
        $(document).ready(function() {
            renderMiniCalendar();
            updateView();
            loadTodayEvents();
            
            // Color Picker
            $('.color-option').click(function() {
                $('.color-option').removeClass('selected');
                $(this).addClass('selected');
                selectedColor = $(this).data('color');
            });

            // Event Form Submit
            $('#eventForm').submit(function(e) {
                e.preventDefault();
                saveEvent();
            });

            // Datumssuche Enter
            $('#dateSearch').keypress(function(e) {
                if (e.which === 13) searchDate();
            });

            // Auto-Format Datumssuche
            $('#dateSearch').on('input', function() {
                let val = $(this).val().replace(/\D/g, '');
                if (val.length >= 2) val = val.substr(0,2) + '.' + val.substr(2);
                if (val.length >= 5) val = val.substr(0,5) + '.' + val.substr(5,4);
                $(this).val(val);
            });
        });

        // Events laden
        function loadEvents(start, end, callback) {
            $.post('', {
                ajax: true,
                action: 'getEvents',
                start: start,
                end: end
            }, function(data) {
                allEvents = data;
                if (callback) callback();
            }, 'json');
        }

        // Event speichern
        function saveEvent() {
            const eventData = {
                ajax: true,
                action: 'addEvent',
                title: $('#eventTitle').val(),
                date: $('#eventDate').val(),
                time_start: $('#eventTimeStart').val(),
                time_end: $('#eventTimeEnd').val() || null,
                color: selectedColor,
                description: $('#eventDescription').val()
            };

            $.post('', eventData, function(response) {
                if (response.success) {
                    closeModal();
                    updateView();
                    loadTodayEvents();
                    renderMiniCalendar();
                }
            }, 'json');
        }

        // Event löschen
        function deleteEvent() {
            if (!confirm('Termin wirklich löschen?')) return;
            
            const id = $('#eventId').val();
            $.post('', {
                ajax: true,
                action: 'deleteEvent',
                id: id
            }, function(response) {
                if (response.success) {
                    closeModal();
                    updateView();
                    loadTodayEvents();
                    renderMiniCalendar();
                }
            }, 'json');
        }

        // Modal öffnen
        function openEventModal(date, time, event) {
            $('#eventForm')[0].reset();
            $('#eventId').val('');
            $('#deleteBtn').hide();
            $('.color-option').removeClass('selected');
            $('.color-option[data-color="#3b82f6"]').addClass('selected');
            selectedColor = '#3b82f6';

            if (event) {
                $('#modalTitle').text('Termin bearbeiten');
                $('#eventId').val(event.id);
                $('#eventTitle').val(event.title);
                $('#eventDate').val(event.date);
                $('#eventTimeStart').val(event.time_start);
                $('#eventTimeEnd').val(event.time_end || '');
                $('#eventDescription').val(event.description || '');
                $('.color-option').removeClass('selected');
                $(`.color-option[data-color="${event.color}"]`).addClass('selected');
                selectedColor = event.color;
                $('#deleteBtn').show();
            } else {
                $('#modalTitle').text('Neuer Termin');
                $('#eventDate').val(date);
                if (time) $('#eventTimeStart').val(time);
            }

            $('#eventModal').addClass('active');
        }

        // Modal schließen
        function closeModal() {
            $('#eventModal').removeClass('active');
        }

        // View wechseln
        function changeView(view) {
            currentView = view;
            $('.view-btn').removeClass('active');
            $(`.view-btn[data-view="${view}"]`).addClass('active');
            updateView();
        }

        // Navigation
        function navigateView(delta) {
            if (currentView === 'day') {
                currentDate.setDate(currentDate.getDate() + delta);
            } else if (currentView === 'week') {
                currentDate.setDate(currentDate.getDate() + (delta * 7));
            } else if (currentView === 'month') {
                currentDate.setMonth(currentDate.getMonth() + delta);
            }
            updateView();
        }

        function goToToday() {
            currentDate = new Date();
            updateView();
        }

        // View aktualisieren
        function updateView() {
            updateCurrentDateDisplay();
            
            if (currentView === 'day') {
                renderDayView();
            } else if (currentView === 'week') {
                renderWeekView();
            } else if (currentView === 'month') {
                renderMonthView();
            }
        }

        // Datum-Anzeige aktualisieren
        function updateCurrentDateDisplay() {
            let text = '';
            if (currentView === 'day') {
                text = dayNames[currentDate.getDay()] + ', ' + 
                       currentDate.getDate() + '. ' + 
                       monthNames[currentDate.getMonth()] + ' ' + 
                       currentDate.getFullYear();
            } else if (currentView === 'week') {
                const weekStart = getWeekStart(currentDate);
                const weekEnd = new Date(weekStart);
                weekEnd.setDate(weekEnd.getDate() + 6);
                text = weekStart.getDate() + '. ' + monthNames[weekStart.getMonth()] + ' - ' +
                       weekEnd.getDate() + '. ' + monthNames[weekEnd.getMonth()] + ' ' + weekEnd.getFullYear();
            } else if (currentView === 'month') {
                text = monthNames[currentDate.getMonth()] + ' ' + currentDate.getFullYear();
            }
            $('#currentDate').text(text);
        }

        // Tagesansicht rendern
        function renderDayView() {
            const dateStr = formatDate(currentDate);
            const start = dateStr;
            const end = dateStr;

            loadEvents(start, end, function() {
                let html = '<div class="day-view"><div class="time-slots">';
                
                for (let h = 0; h < 24; h++) {
                    const timeStr = h.toString().padStart(2, '0') + ':00';
                    const events = allEvents.filter(e => {
                        if (e.date !== dateStr) return false;
                        const eventHour = parseInt(e.time_start.split(':')[0]);
                        return eventHour === h;
                    });

                    html += `<div class="time-slot">
                        <div class="time-label">${timeStr}</div>
                        <div class="time-content" onclick="openEventModal('${dateStr}', '${timeStr}')">`;
                    
                    events.forEach(event => {
                        html += `<div class="event-card" style="border-color: ${event.color}; background: ${event.color}20" onclick="event.stopPropagation(); openEventModal('', '', ${JSON.stringify(event).replace(/"/g, '&quot;')})">
                            <div class="event-time">${event.time_start} ${event.time_end ? '- ' + event.time_end : ''}</div>
                            <div class="event-title">${event.title}</div>
                        </div>`;
                    });

                    html += '</div></div>';
                }

                html += '</div></div>';
                $('#calendarView').html(html);
            });
        }

        // Wochenansicht rendern
        function renderWeekView() {
            const weekStart = getWeekStart(currentDate);
            const weekEnd = new Date(weekStart);
            weekEnd.setDate(weekEnd.getDate() + 6);

            const start = formatDate(weekStart);
            const end = formatDate(weekEnd);

            loadEvents(start, end, function() {
                let html = '<div class="week-view"><div class="week-grid">';
                
                // Header
                html += '<div class="week-header"></div>';
                const today = formatDate(new Date());
                
                for (let i = 0; i < 7; i++) {
                    const day = new Date(weekStart);
                    day.setDate(day.getDate() + i);
                    const dayStr = formatDate(day);
                    const isToday = dayStr === today;
                    
                    html += `<div class="week-header ${isToday ? 'today-col' : ''}">
                        <div class="week-day-name">${shortDayNames[day.getDay()]}</div>
                        <div class="week-day-num">${day.getDate()}</div>
                    </div>`;
                }

                // Time slots
                for (let h = 8; h <= 20; h++) {
                    const timeStr = h.toString().padStart(2, '0') + ':00';
                    html += `<div class="week-time-label">${timeStr}</div>`;

                    for (let i = 0; i < 7; i++) {
                        const day = new Date(weekStart);
                        day.setDate(day.getDate() + i);
                        const dayStr = formatDate(day);
                        const isToday = dayStr === today;

                        const events = allEvents.filter(e => {
                            if (e.date !== dayStr) return false;
                            const eventHour = parseInt(e.time_start.split(':')[0]);
                            return eventHour === h;
                        });

                        html += `<div class="week-time-cell ${isToday ? 'today-col' : ''}" onclick="openEventModal('${dayStr}', '${timeStr}')">`;
                        
                        events.forEach(event => {
                            html += `<div class="week-event" style="border-color: ${event.color}; background: ${event.color}20" onclick="event.stopPropagation(); openEventModal('', '', ${JSON.stringify(event).replace(/"/g, '&quot;')})">
                                ${event.time_start} ${event.title}
                            </div>`;
                        });

                        html += '</div>';
                    }
                }

                html += '</div></div>';
                $('#calendarView').html(html);
            });
        }

        // Monatsansicht rendern
        function renderMonthView() {
            const year = currentDate.getFullYear();
            const month = currentDate.getMonth();
            const firstDay = new Date(year, month, 1);
            const lastDay = new Date(year, month + 1, 0);
            
            const startDate = new Date(firstDay);
            startDate.setDate(startDate.getDate() - (firstDay.getDay() === 0 ? 6 : firstDay.getDay() - 1));
            
            const endDate = new Date(lastDay);
            endDate.setDate(endDate.getDate() + (7 - (lastDay.getDay() === 0 ? 7 : lastDay.getDay())));

            const start = formatDate(startDate);
            const end = formatDate(endDate);

            loadEvents(start, end, function() {
                let html = '<div class="month-view"><div class="month-grid">';
                
                // Weekday headers
                const weekdayOrder = ['Mo', 'Di', 'Mi', 'Do', 'Fr', 'Sa', 'So'];
                weekdayOrder.forEach(day => {
                    html += `<div class="month-weekday">${day}</div>`;
                });

                // Days
                const today = formatDate(new Date());
                const current = new Date(startDate);

                while (current <= endDate) {
                    const dayStr = formatDate(current);
                    const isToday = dayStr === today;
                    const isOtherMonth = current.getMonth() !== month;
                    
                    const dayEvents = allEvents.filter(e => e.date === dayStr);
                    const visibleEvents = dayEvents.slice(0, 3);
                    const moreCount = dayEvents.length - 3;

                    html += `<div class="month-day ${isOtherMonth ? 'other-month' : ''} ${isToday ? 'today' : ''}" onclick="selectDayFromMonth('${dayStr}')">
                        <div class="month-day-num">${current.getDate()}</div>
                        <div class="month-events">`;
                    
                    visibleEvents.forEach(event => {
                        html += `<div class="month-event" style="border-color: ${event.color}; background: ${event.color}20" onclick="event.stopPropagation(); openEventModal('', '', ${JSON.stringify(event).replace(/"/g, '&quot;')})">
                            ${event.time_start} ${event.title}
                        </div>`;
                    });

                    if (moreCount > 0) {
                        html += `<div class="more-events">+${moreCount} weitere</div>`;
                    }

                    html += '</div></div>';
                    current.setDate(current.getDate() + 1);
                }

                html += '</div></div>';
                $('#calendarView').html(html);
            });
        }

        // Tag aus Monatsansicht auswählen
        function selectDayFromMonth(dateStr) {
            const parts = dateStr.split('-');
            currentDate = new Date(parts[0], parts[1] - 1, parts[2]);
            changeView('day');
        }

        // Mini-Kalender rendern
        function renderMiniCalendar() {
            const year = miniCalendarDate.getFullYear();
            const month = miniCalendarDate.getMonth();
            const firstDay = new Date(year, month, 1);
            const lastDay = new Date(year, month + 1, 0);
            
            $('#miniMonthYear').text(monthNames[month] + ' ' + year);

            const startDate = new Date(firstDay);
            startDate.setDate(startDate.getDate() - (firstDay.getDay() === 0 ? 6 : firstDay.getDay() - 1));
            
            // Events für Mini-Kalender laden
            const start = formatDate(startDate);
            const endDate = new Date(lastDay);
            endDate.setDate(endDate.getDate() + 7);
            const end = formatDate(endDate);

            $.post('', {
                ajax: true,
                action: 'getEvents',
                start: start,
                end: end
            }, function(events) {
                let html = '';
                
                // Weekdays
                const weekdayOrder = ['Mo', 'Di', 'Mi', 'Do', 'Fr', 'Sa', 'So'];
                weekdayOrder.forEach(day => {
                    html += `<div class="mini-weekday">${day}</div>`;
                });

                // Days
                const today = formatDate(new Date());
                const selected = formatDate(currentDate);
                const current = new Date(startDate);

                for (let i = 0; i < 42; i++) {
                    const dayStr = formatDate(current);
                    const isToday = dayStr === today;
                    const isSelected = dayStr === selected;
                    const isOtherMonth = current.getMonth() !== month;
                    const hasEvents = events.some(e => e.date === dayStr);

                    html += `<div class="mini-day ${isOtherMonth ? 'other-month' : ''} ${isToday ? 'today' : ''} ${isSelected ? 'selected' : ''} ${hasEvents ? 'has-events' : ''}" onclick="selectMiniDay('${dayStr}')">
                        ${current.getDate()}
                    </div>`;
                    
                    current.setDate(current.getDate() + 1);
                }

                $('#miniCalendar').html(html);
            }, 'json');
        }

        // Mini-Kalender Navigation
        function navigateMiniMonth(delta) {
            miniCalendarDate.setMonth(miniCalendarDate.getMonth() + delta);
            renderMiniCalendar();
        }

        // Tag aus Mini-Kalender auswählen
        function selectMiniDay(dateStr) {
            const parts = dateStr.split('-');
            currentDate = new Date(parts[0], parts[1] - 1, parts[2]);
            miniCalendarDate = new Date(currentDate);
            changeView('day');
            renderMiniCalendar();
        }

        // Heutige Termine laden
        function loadTodayEvents() {
            const today = formatDate(new Date());
            $.post('', {
                ajax: true,
                action: 'getEvents',
                start: today,
                end: today
            }, function(events) {
                let html = '';
                
                if (events.length === 0) {
                    html = '<p style="color: #999; font-size: 14px;">Keine Termine heute</p>';
                } else {
                    events.forEach(event => {
                        html += `<div class="today-event" style="border-color: ${event.color}" onclick="openEventModal('', '', ${JSON.stringify(event).replace(/"/g, '&quot;')})">
                            <div class="today-event-time">${event.time_start} ${event.time_end ? '- ' + event.time_end : ''}</div>
                            <div class="today-event-title">${event.title}</div>
                        </div>`;
                    });
                }

                $('#todayEvents').html(html);
            }, 'json');
        }

        // Datumssuche
        function searchDate() {
            const input = $('#dateSearch').val();
            const parts = input.split('.');
            
            if (parts.length !== 3) {
                alert('Bitte Datum im Format TT.MM.JJJJ eingeben');
                return;
            }

            const day = parseInt(parts[0]);
            const month = parseInt(parts[1]) - 1;
            const year = parseInt(parts[2]);

            if (isNaN(day) || isNaN(month) || isNaN(year) || day < 1 || day > 31 || month < 0 || month > 11 || year < 2000 || year > 2100) {
                alert('Ungültiges Datum');
                return;
            }

            currentDate = new Date(year, month, day);
            miniCalendarDate = new Date(currentDate);
            changeView('day');
            renderMiniCalendar();
            $('#dateSearch').val('');
        }

        // Hilfsfunktionen
        function formatDate(date) {
            const year = date.getFullYear();
            const month = (date.getMonth() + 1).toString().padStart(2, '0');
            const day = date.getDate().toString().padStart(2, '0');
            return `${year}-${month}-${day}`;
        }

        function getWeekStart(date) {
            const d = new Date(date);
            const day = d.getDay();
            const diff = d.getDate() - (day === 0 ? 6 : day - 1);
            return new Date(d.setDate(diff));
        }
    </script>
</body>
</html>