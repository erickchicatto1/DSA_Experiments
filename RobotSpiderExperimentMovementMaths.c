/* USER CODE BEGIN 0 */

#define KP 0.5 // Constante proporcional para el ajuste del centro de masa
#define TARGET_COG_X 0 // Centro de masa ideal en X
#define TARGET_COG_Y 0 // Centro de masa ideal en Y

// Función para calcular el centro de masa (COG) del robot
void CalculateCOG(float legPositions[4][2], float* cogX, float* cogY) {
    *cogX = 0;
    *cogY = 0;
    for (int i = 0; i < 4; i++) {
        *cogX += legPositions[i][0];
        *cogY += legPositions[i][1];
    }
    *cogX /= 4.0; // Promedio de X
    *cogY /= 4.0; // Promedio de Y
}

// Función para ajustar los ángulos de las patas
void AdjustLegAngles(float legPositions[4][2], uint8_t legChannels[4][3]) {
    float cogX, cogY;
    CalculateCOG(legPositions, &cogX, &cogY);

    float errorX = TARGET_COG_X - cogX;
    float errorY = TARGET_COG_Y - cogY;

    for (int i = 0; i < 4; i++) {
        // Calcular correcciones proporcionales
        float correctionX = KP * errorX;
        float correctionY = KP * errorY;

        // Ajustar las posiciones en el espacio cartesiano
        legPositions[i][0] += correctionX;
        legPositions[i][1] += correctionY;

        // Calcular los ángulos para cada servomotor
        float baseAngle = atan2(legPositions[i][1], legPositions[i][0]) * (180.0 / M_PI);
        float femurAngle = 90; // Fijo para simplificación (puedes calcularlo dinámicamente)
        float tibiaAngle = 120; // Ajustable según diseño

        // Configurar los ángulos de los servos usando PCA9685_SetServoAngle
        PCA9685_SetServoAngle(legChannels[i][0], baseAngle);  // Base
        PCA9685_SetServoAngle(legChannels[i][1], femurAngle); // Fémur
        PCA9685_SetServoAngle(legChannels[i][2], tibiaAngle); // Tibia
    }
}

// Secuencia de movimiento optimizada
void OptimizedMoveForward(uint8_t legChannels[4][3]) {
    float legPositions[4][2] = {
        {10, 20}, // Pata 1: (x, y)
        {10, -20}, // Pata 2: (x, y)
        {-10, 20}, // Pata 3: (x, y)
        {-10, -20} // Pata 4: (x, y)
    };

    // Ajuste dinámico durante la caminata
    for (int step = 0; step < 3; step++) {
        AdjustLegAngles(legPositions, legChannels);
        HAL_Delay(500); // Pausa entre ajustes
    }
}

/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
PCA9685_Init(50); // Inicializar PCA9685 para 50 Hz

// Mapear los canales del PCA9685 a los motores de las patas
uint8_t legChannels[4][3] = {
    {5, 6, 7},  // Pata 1: Base, Fémur, Tibia
    {8, 9, 10}, // Pata 2: Base, Fémur, Tibia
    {11, 12, 13}, // Pata 3: Base, Fémur, Tibia
    {14, 15, 16}  // Pata 4: Base, Fémur, Tibia
};
/* USER CODE END 2 */

/* Infinite loop */
/* USER CODE BEGIN WHILE */
while (1) {
    OptimizedMoveForward(legChannels); // Ejecutar movimiento hacia adelante
    HAL_Delay(1000); // Pausa entre ciclos
}
/* USER CODE END WHILE */
