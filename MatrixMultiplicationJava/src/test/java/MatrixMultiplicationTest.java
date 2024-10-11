public class MatrixMultiplicationTest {

    public static void main(String[] args) {
        int[] matrixSizes = {256, 512, 1024, 2048};
        int runsPerSize = 5;

        for (int size : matrixSizes) {
            System.out.println("=== Tamaño de Matriz: " + size + "x" + size + " ===");
            double totalTime = 0.0;
            long totalMemory = 0;

            for (int run = 1; run <= runsPerSize; run++) {
                MatrixMultiplication mm = new MatrixMultiplication(size);
                mm.initializeMatrices();
                long memoryBefore = getUsedMemory();
                long startTime = System.nanoTime();
                mm.multiply();
                long endTime = System.nanoTime();
                long memoryAfter = getUsedMemory();
                double elapsedTime = (endTime - startTime) / 1e9;
                totalTime += elapsedTime;
                long memoryUsed = (memoryAfter - memoryBefore) / (1024 * 1024);
                totalMemory += memoryUsed;
                System.out.printf("Ejecución %d: Tiempo = %.3f segundos, Memoria Usada = %d MB%n",
                        run, elapsedTime, memoryUsed);
            }
            double averageTime = totalTime / runsPerSize;
            double averageMemory = (double) totalMemory / runsPerSize;
            System.out.printf("Promedio: Tiempo = %.3f segundos, Memoria Promedio Usada = %.2f MB%n%n",
                    averageTime, averageMemory);
        }
    }

    private static long getUsedMemory() {
        Runtime runtime = Runtime.getRuntime();
        return runtime.totalMemory() - runtime.freeMemory();
    }
}
