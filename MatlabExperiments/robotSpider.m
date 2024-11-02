clear a;
a = arduino('COM9', 'Due', 'Libraries', 'Servo');
s = servo(a, 'D4', 'MinPulseDuration', 600e-6, 'MaxPulseDuration', 2400e-6);

potPin = 'A0'; % Pin analógico al que está conectado el potenciómetro

while true
    % Leer el valor del potenciómetro (valor entre 0 y 5V)
    potValue = readVoltage(a, potPin);
    
    % Convertir el valor de voltaje a un ángulo en grados (0 a 180)
    angle_deg = (potValue / 5) * 180; % Escalar el valor a un rango de 0 a 180 grados
    
    % Convertir el ángulo en grados a un valor entre 0 y 1 para writePosition
    angle = angle_deg / 180;
    writePosition(s, angle);
    
    % Mostrar la posición actual en grados
    fprintf('Current motor position is %.2f degrees\n', angle_deg);
    
    % Pausa pequeña para que el código no se ejecute demasiado rápido
    pause(0.1);
end
