% Conectar el Arduino Due
a = arduino('COM9', 'Due');  % Cambia 'COM3' al puerto donde está conectado tu Arduino Due

% Configura el pin 13 como salida
configurePin(a, 'D13', 'DigitalOutput');

% Parpadeo del LED
for i = 1:10  % Número de parpadeos
    writeDigitalPin(a, 'D13', 1);  % Encender LED
    pause(0.5);                    % Esperar 0.5 segundos
    writeDigitalPin(a, 'D13', 0);  % Apagar LED
    pause(0.5);                    % Esperar 0.5 segundos
end

% Liberar el Arduino
clear a;



