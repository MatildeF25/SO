
ALTER TABLE `Investigador`
ADD `Data_Nacismento` DATE NOT NULL;
ADD `eMail` VARCHAR(75) NOT NULL;

SELECT Projeto
FROM Projeto
JOIN Investigador ON Projeto.id = Investigador.Projeto 
WHERE Investigador.Categoria = 'A' AND Projeto.Orcamento > 100000.00;

CREATE VIEW ex3 AS 
SELECT Investigador.Nome
FROM Investigador
JOIN Projeto ON Investigador.Projeto = Projeto.id 
ORDER BY Projeto.Orcamento DESC;

DELETE InvestigadorTarefa WHERE Tarefa IN (SELECT Id FROM Tarefa WHERE Tarefa.Designacao = 'Limpeza de Microscópio');
DELETE Tarefa WHERE Tarefa.Designacao = 'Limpeza de Microscópio';

CREATE FUNCTION ObterTempoTotal(investigador_id INT) RETURNS TIME
BEGIN
    DECLARE TempoTotal TIME;

    SELECT SEC_TO_TIME(SUM(TIME_TO_SEC(InvestigadorTarefa.Duracao))) INTO TempoTotal
    FROM InvestigadorTarefa
    JOIN Investigador ON InvestigadorTarefa.Investigador = Investigador.id
    WHERE Investigador.id = investigador_id;

    RETURN tempo_total;
END;

------------------------------------------------------------------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS `Explicacoes` 
(
    `id` INT NOT NULL AUTO_INCREMENT,
    `Data` DATE NOT NULL,
    `HoraInicio` TIME NOT NULL,
    `HoraFim` TIME NOT NULL,
    `Disciplina` INT NOT NULL,
    `Monitor` INT NOT NULL,
    `Estudante` INT NOT NULL,
    `Sumario` VARCHAR(150) NOT NULL,
    `Observacoes` TEXT,
    PRIMARY KEY (`id`),
    INDEX `fk_Explicacoes_Disciplina1_idx` (`Disciplina` ASC),
    CONSTRAINT `fk_Explicacoes_Disciplina1`
        FOREIGN KEY (`Disciplina`)
        REFERENCES `Disciplina` (`id`)
        ON DELETE NO ACTION
        ON UPDATE NO ACTION,
    INDEX `fk_Explicacoes_Monitor1_idx` (`Monitor` ASC),
    CONSTRAINT `fk_Explicacoes_Monitor1`
        FOREIGN KEY (`Monitor`)
        REFERENCES `Monitor` (`id`)
        ON DELETE NO ACTION
        ON UPDATE NO ACTION,
    INDEX `fk_Explicacoes_Estudante1_idx` (`Estudante` ASC),
    CONSTRAINT `fk_Explicacoes_Estudante1`
        FOREIGN KEY (`Estudante`)
        REFERENCES `Estudante` (`id`)
        ON DELETE NO ACTION
        ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


SELECT Estudante.Nome
FROM Estudante
JOIN Explicacoes ON Estudante.Nr = Explicacoes.Estudante
JOIN Monitor ON Explicacoes.Monitor = Monitor.Nr
WHERE Explicacoes.Data >= '2018-12-01' AND Explicacoes.Data <= '2018-12-31'
AND Monitor.Nome IN ('Josefa Bracara Silva', 'Alberto Ramos Pinto');


DELETE Explicacoes WHERE Estudante IN (SELECT Id FROM Estudante WHERE Estudante.Ano = 4 AND Estudante.Escola = 'Ases do Saber');


CREATE PROCEDURE GetTotalHorasExplicacoes (IN alunoId INT, IN disciplinaId INT)
BEGIN
    DECLARE horaInicio TIME;
    DECLARE horaFim TIME;
    DECLARE totalHoras TIME;

    SELECT HoraInicio INTO horaInicio
    FROM Explicacoes
    WHERE Explicacoes.Estudante = alunoId AND Explicacoes.Disciplina = disciplinaId

    SELECT HoraFim INTO horaFim
    FROM Explicacoes
    WHERE Explicacoes.Estudante = alunoId AND Explicacoes.Disciplina = disciplinaId

    SET totalHoras  = TIMEDIFF(horaFim, horaInicio);

    IF totalHoras IS NOT NULL THEN
          SELECT totalHoras AS 'Total de horas de explicação';
    ELSE
        SELECT 'Nenhuma explicação encontrada para o aluno.';
    END IF;
END;

----------------------------------------------------------------------------------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS `AutorLivro`
(
    `Autor`   INTEGER NOT NULL,
    `Livro`   INTEGER NOT NULL,
    INDEX `fk_AutorLivro_Livro1_idx` (`Livro` ASC),
    CONSTRAINT `fk_AutorLivro_Livro1`
        FOREIGN KEY (`Livro`)
        REFERENCES `Livro` (`id`)
        ON DELETE NO ACTION
        ON UPDATE NO ACTION,
    INDEX `fk_AutorLivro_Autor1_idx` (`Autor` ASC),
    CONSTRAINT `fk_AutorLivro_Autor1`
        FOREIGN KEY (`Autor`)
        REFERENCES `Autor` (`id`)
        ON DELETE NO ACTION
        ON UPDATE NO ACTION
);


SELECT * FROM Livro
JOIN Editora ON Livro.Editora = Editora.id
WHERE Editora.Designacao = 'Prensar'
ORDER BY Livro.Titulo ASC;


SELECT Autor.Nome
FROM Autores
JOIN AutorLivro ON Autor.id = AutorLivro.Autor
JOIN Livro ON AutorLivro.Livro = Livro.id
JOIN Categoria ON Livro.Categoria = Categoria.id
WHERE Categoria.Designacao = 'Aventura' AND Livro.Data_Lancamento >= '2020-01-01' AND Livro.Data_Lancamento <= '2020-12-31'


DELETE Livro WHERE Livro.Critica LIKE '%razoavel%';

CREATE PROCEDURE GetCritica (IN livro_id INT)
BEGIN
    DECLARE Critica_livro TEXT

    SELECT Critica INTO Critica_livro
    FROM Livro
    WHERE Livro.id = livro_id

    IF Critica_livro IS NOT NULL THEN
        SELECT Critica_livro AS 'Critica do Livro';
    ELSE
        SELECT 'Nenhuma critica encontrada para o livro.';
    END IF;
END;




















